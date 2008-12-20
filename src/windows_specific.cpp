/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2007, the VVV Development team

	Author: Fulvio Senore

    VVV is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    VVV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VVV; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// Windows specific code
// compile only for the Windows version

#include <windows.h>
#include <io.h>
#include <wx/app.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include "catalog_volume_functions.h"
#include "catalog_volume.h"
#include "windows_specific.h"
#include "audio_metadata.h"
#include "data_interface/volumes.h"
#include "data_interface/paths.h"
#include "data_interface/files.h"
#include "data_interface/files_audio_metadata.h"

// return the name of a volume specified in a way like "C:\"
// return an empty string in case of error
wxString GetVolumeName( wxString volume ) {
	TCHAR vn[50];
	DWORD mcl, fsf;
	wxString retVal;

	if( GetVolumeInformation( volume.c_str(), vn, 49, NULL, &mcl, &fsf, NULL, 0 ) )
		retVal = vn;
	else
		retVal = wxEmptyString;
	
	return retVal;
}

// return the datetime and size of the current file
void GetFileDateSizeWindows( WIN32_FIND_DATA &ffd, wxDateTime &FileDateTime, wxLongLong &FileSize ) {
	SYSTEMTIME stLocal;
	FILETIME ft;
	FileTimeToLocalFileTime( &ffd.ftLastWriteTime, &ft );
	FileTimeToSystemTime(&ft, &stLocal);
	FileDateTime.Set( stLocal.wDay, (wxDateTime::Month) (stLocal.wMonth - 1), stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond, stLocal.wMilliseconds );
	FileSize = ( ((__int64)ffd.nFileSizeHigh) << 32 ) + ffd.nFileSizeLow;
}

// add a file to the database
// this function is not a member of CCatalogVolumeFunction to avoid problems with the definition of WIN32_FIND_DATA
void AddFileToDBWindows( WIN32_FIND_DATA &ffd, wxString &path, CNullableLong& PathID ) {
	CFiles file;
	file.FileName = ffd.cFileName;
	wxFileName fn( path, file.FileName );
	file.FileExt = fn.GetExt();
	if( file.FileExt.Len() > 30 ) file.FileExt = wxEmptyString;	// such a long extension is surely a meaningless temporary file
	
	wxDateTime fTime;
	wxLongLong fSize;
	GetFileDateSizeWindows( ffd, fTime, fSize );
	file.DateTime = fTime;
	file.FileSize = fSize;

	file.PathID = PathID;
	file.PathFileID.SetNull(true);
	file.DbInsert();

	if( file.FileExt == wxT("mp3") ) {
		CFilesAudioMetadata metaData;
		if( CAudioMetadata::ReadMP3Metadata( fn.GetFullPath(), metaData ) ) {
			metaData.FileID = file.FileID;
			metaData.DbInsert();
		}
	}
}

void CCatalogVolumeFunctions::AddFolderToDBWindows( _tfinddata_t &c_file, wxString &path, CNullableLong &PathID, CBaseDB* db, long VolumeID ) {

	wxFileName dirName( path, wxEmptyString );
	dirName.AppendDir( c_file.name );

	CFiles file;
	file.FileName = c_file.name;
	file.FileExt = wxEmptyString;
	file.DateTime = c_file.time_write;
	file.FileSize = 0;
	file.PathID = PathID;

	CNullableLong nl;
	nl.SetNull( true );
	CatalogUpdateSingleFolderWindows( db, dirName.GetPath(), VolumeID, nl, PathID, &file );
}

void CCatalogVolumeFunctions::CatalogUpdateSingleFolderWindows( CBaseDB* db, wxString path, long VolumeID, CNullableLong PathID, CNullableLong& FatherID, CFiles* PathFile  ) {
	bool doUpdate = (!PathID.IsNull());	// true if we must update the folder, false if we must catalog it

	wxString fileName;
	wxString winPath;	// path to be used for Windows-specific calls

	// used when updating: it will contain the list of files or folders already stored in the database
	map<wxString, CFileData> folderFiles;
	map<wxString, CFileData>::iterator ffi;

	winPath = path;
	if( !winPath.EndsWith(wxT("\\")) )
		winPath += wxT("\\");
	winPath += wxT("*.*");

	// shows the path in the dialog box
	if( statText != NULL ) {
		statText->SetLabel( path );
		wxTheApp->Yield();
	}

	if( doUpdate ) {
		// fill the map object with the content of the current folder
		ReadFolderFilesFromDB( folderFiles, PathID );
	}
	else {
		// writes the path row
		PathID = WritePathRow( path, VolumeID, FatherID );
	}

	// adds the path id and stores the FILES info about this folder
	if( PathFile != NULL ) {
		PathFile->PathFileID = PathID;
		PathFile->DbInsert();
	}

	// reads all file names
	WIN32_FIND_DATA ffd;
	HANDLE sh = FindFirstFile( winPath.c_str(), &ffd );
	if( sh != INVALID_HANDLE_VALUE ) {
		do {
			if( !(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
				// exclude folders

				// see if the file is already present
				// if we are cataloging the folder the map object is empty so we always add
				ffi = folderFiles.find( ffd.cFileName );
				if( ffi == folderFiles.end() ) {
					// not found, add the file to the database
					AddFileToDBWindows( ffd, path, PathID );
					nAddedFiles++;
				}
				else {
					ffi->second.IsStillThere = true;
					// check if file date or size have changed
					wxDateTime fTime;
					wxLongLong fSize;
					GetFileDateSizeWindows( ffd, fTime, fSize );
					if( !fTime.IsEqualUpTo(ffi->second.DateTime, wxTimeSpan::Seconds(10)) || fSize != ffi->second.FileSize ) {
						CFiles::UpdateDateSize( ffi->second.FileID, fTime, fSize );
						nUpdatedFiles++;
					}
					else {
						nUnchangedFiles++;
					}
				}
			}
		} while( FindNextFile(sh, &ffd) );
	}
	FindClose( sh );

	// scan the map looking for files to be deleted
	ffi = folderFiles.begin();
	while( ffi != folderFiles.end() ) {
		if( !ffi->second.IsStillThere && !ffi->second.IsFolder ) {
			// we need to delete this file
			CFiles file;
			file.FileID = ffi->second.FileID;
			file.DbDelete();
			nDeletedFiles++;
		}
		ffi++;
	}

	// now reads all the subfolders
	_tfinddata_t c_file;
	intptr_t hFile = _tfindfirst( winPath.c_str(), &c_file );
	if( hFile != -1L ) {
		do {
			if( (c_file.attrib & _A_SUBDIR) && (_tcscmp(c_file.name, wxT(".")) != 0) && (_tcscmp(c_file.name, wxT("..")) != 0) ) {
				// see if the folder is already present
				ffi = folderFiles.find( c_file.name );
				if( ffi == folderFiles.end() ) {
					// new folder, we add it to the DB
					AddFolderToDBWindows( c_file, path, PathID, db, VolumeID );
				}		
				else {
					// the folder is already in the DB, scan it
					ffi->second.IsStillThere = true;
					wxFileName dirName( path, wxEmptyString );
					dirName.AppendDir( c_file.name );
					CatalogUpdateSingleFolderWindows( db, dirName.GetPath(), VolumeID, ffi->second.PathFileID, PathID, NULL );
				}
			}
		} while( _tfindnext( hFile, &c_file ) == 0 );
	}
	_findclose( hFile );

	// scan the map looking for folders to be deleted
	ffi = folderFiles.begin();
	while( ffi != folderFiles.end() ) {
		if( !ffi->second.IsStillThere && ffi->second.IsFolder ) {
			// we need to delete this folder
			CPaths path;
			path.PathID = ffi->second.PathFileID;
			path.DbDelete();
			nDeletedFolders++;
		}
		ffi++;
	}
}


