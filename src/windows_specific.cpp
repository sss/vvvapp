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

// Windows specific version of CatalogSingleFolder to gain speed
void CCatalogVolumeFunctions::CatalogSingleFolderWindows( CBaseDB* db, wxString path, long VolumeID, CNullableLong& FatherID, CFiles* PathFile  ) {
	wxString fileName;
	wxString winPath;	// path to be used for Windows-specific calls

	winPath = path;
	if( !winPath.EndsWith(wxT("\\")) )
		winPath += wxT("\\");
	winPath += wxT("*.*");

	// shows the path in the dialog box
	if( statText != NULL ) {
		statText->SetLabel( path );
		wxSafeYield();
	}

	// writes the path row
	wxFileName dirName( path, wxEmptyString );
	CPaths pth;
	pth.VolumeID = VolumeID;
	pth.PathName = dirName.GetPath(0);
	pth.PathName = pth.PathName.AfterLast( wxFileName::GetPathSeparator() );	// only takes the last part of the full path
	pth.FatherID = FatherID;
	pth.DbInsert();

	// adds the path id and stores the FILES info about this folder
	if( PathFile != NULL ) {
		PathFile->PathFileID = pth.PathID;
		PathFile->DbInsert();
	}

	// reads all file names
	WIN32_FIND_DATA ffd;
	HANDLE sh = FindFirstFile( winPath.c_str(), &ffd );
	if( sh != INVALID_HANDLE_VALUE ) {
		do {
			if( !(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
				// exclude folders
				CFiles file;
				file.FileName = ffd.cFileName;
				wxFileName fn( path, file.FileName );
				file.FileExt = fn.GetExt();
				if( file.FileExt.Len() > 30 ) file.FileExt = wxEmptyString;	// such a long extension is surely a meaningless temporary file
				
				SYSTEMTIME stLocal;
				FILETIME ft;
				FileTimeToLocalFileTime( &ffd.ftLastWriteTime, &ft );
				FileTimeToSystemTime(&ft, &stLocal);
				file.DateTime.Set( stLocal.wDay, (wxDateTime::Month) (stLocal.wMonth - 1), stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond, stLocal.wMilliseconds );

				file.FileSize = ( ((__int64)ffd.nFileSizeHigh) << 32 ) + ffd.nFileSizeLow;
				file.PathID = pth.PathID;
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
		} while( FindNextFile(sh, &ffd) );
	}
	FindClose( sh );

	// now reads all the subfolders
	struct _tfinddata_t c_file;
	intptr_t hFile = _tfindfirst( winPath.c_str(), &c_file );
	if( hFile != -1L ) {
		do {
			if( (c_file.attrib & _A_SUBDIR) && (_tcscmp(c_file.name, wxT(".")) != 0) && (_tcscmp(c_file.name, wxT("..")) != 0) ) {
				wxFileName dirName( path, wxEmptyString );
				dirName.AppendDir( c_file.name );

				CFiles file;
				file.FileName = c_file.name;
				file.FileExt = wxEmptyString;
				file.DateTime = c_file.time_write;
				file.FileSize = 0;
				file.PathID = pth.PathID;

				CatalogSingleFolderWindows( db, dirName.GetPath(), VolumeID, pth.PathID, &file );
			}
		} while( _tfindnext( hFile, &c_file ) == 0 );
	}
	_findclose( hFile );

}

