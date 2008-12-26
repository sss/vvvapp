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

#include "catalog_volume_functions.h"

#include <wx/app.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/config.h>
#include <wx/dirdlg.h>
#include <wx/filefn.h>

#include "audio_metadata.h"
#include "data_interface/volumes.h"
#include "data_interface/paths.h"
#include "data_interface/files.h"
#include "data_interface/data_error.h"
#include "data_interface/files_audio_metadata.h"


CCatalogVolumeFunctions::CCatalogVolumeFunctions( wxStaticText *statText )
{
	this->statText = statText;
}

CCatalogVolumeFunctions::~CCatalogVolumeFunctions(void)
{
}

void CCatalogVolumeFunctions::CatalogVolume( wxString volumePath, wxString volumeName ) {

	// starts a transaction
	CBaseDB* db = CBaseDB::GetDatabase();
	db->TransactionStart();

	wxFileName dirName( volumePath, wxEmptyString );

	// writes the volume row
	CVolumes vol;
	vol.VolumeName = volumeName;
	try {
		// this will throw a CDataErrorException::ecUnique exception if the volume name is already present
		// to be catched by the caller
		vol.DbInsert();
	}
	catch( CDataErrorException& e ) {
		if( e.GetErrorCause() == CDataErrorException::ecUnique ) {
			db->TransactionRollback();
			throw;
		}
		else
			throw;
	}

	nUpdatedFiles = nAddedFiles = nDeletedFiles = nUnchangedFiles = 0;

	// catalogs the folders
	CNullableLong FatherID;
	FatherID.SetNull(true);
	CNullableLong nl;
	nl.SetNull(true);
#ifdef __WXMSW__
	CatalogUpdateSingleFolderWindows( db, volumePath, vol.VolumeID, nl, FatherID, NULL );
#else
	CatalogUpdateSingleFolder( db, volumePath, vol.VolumeID, nl, FatherID, NULL );
#endif

	// update the database statistics, useful after a massive change
	db->UpdateStatistics( CBaseDB::usPhysical );

	// commits the transaction
	db->TransactionCommit();
}


void CCatalogVolumeFunctions::CatalogUpdateSingleFolder( CBaseDB* db, wxString path, long VolumeID, CNullableLong PathID, CNullableLong& FatherID, CFiles* PathFile  ) {
	bool doUpdate = (!PathID.IsNull());	// true if we must update the folder, false if we must catalog it

	wxString fileName;

	// used when updating: it will contain the list of files or folders already stored in the database
	map<wxString, CFileData> folderFiles;
	map<wxString, CFileData>::iterator ffi;

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
	wxDir dir(path);
	bool cont = dir.GetFirst(&fileName, wxT(""), wxDIR_FILES );
	while( cont ) {

		// see if the file is already present
		// if we are cataloging the folder the map object is empty so we always add
		ffi = folderFiles.find( fileName );
		if( ffi == folderFiles.end() ) {
			// not found, add the file to the database
			AddFileToDB( path, fileName, PathID );
		}
		else {
			ffi->second.IsStillThere = true;
			// check if file date or size have changed
			wxFileName fn( path, fileName );
			wxDateTime fTime = fn.GetModificationTime();
			wxLongLong fSize;
			fSize = fn.GetSize();
			if( !fTime.IsEqualUpTo(ffi->second.DateTime, wxTimeSpan::Seconds(10)) || fSize != ffi->second.FileSize ) {
				CFiles::UpdateDateSize( ffi->second.FileID, fTime, fSize );
				nUpdatedFiles++;
			}
			else {
				nUnchangedFiles++;
			}
		}

		cont = dir.GetNext(&fileName);
	}

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
	cont = dir.GetFirst(&fileName, wxT(""), wxDIR_DIRS );
	while( cont ) {
		// see if the folder is already present
		ffi = folderFiles.find( fileName );
		if( ffi == folderFiles.end() ) {
			// new folder, we add it to the DB
			AddFolderToDB( path, fileName, PathID, db, VolumeID );
		}		
		else {
			// the folder is already in the DB, scan it
			ffi->second.IsStillThere = true;
			wxFileName dirName( path, wxEmptyString );
			dirName.AppendDir( fileName );
			CatalogUpdateSingleFolder( db, dirName.GetPath(), VolumeID, ffi->second.PathFileID, PathID, NULL );
		}

		cont = dir.GetNext(&fileName);
	}

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

long CCatalogVolumeFunctions::WritePathRow( wxString path, long VolumeID, CNullableLong& FatherID ) {
	wxFileName dirName( path, wxEmptyString );
	CPaths pth;
	pth.VolumeID = VolumeID;
	pth.PathName = dirName.GetPath(0);
	pth.PathName = pth.PathName.AfterLast( wxFileName::GetPathSeparator() );	// only takes the last part of the full path
	pth.FatherID = FatherID;
	pth.DbInsert();

	return pth.PathID;
}

void CCatalogVolumeFunctions::ReadFolderFilesFromDB( map<wxString, CFileData> &m, long pathID ) {

	CFiles files;
	files.DBStartQueryListFiles( pathID );
	while( !files.IsEOF() ) {
		CFileData *fd = new CFileData();
		fd->IsFolder = files.IsFolder();
		fd->FileID = files.FileID;
		fd->DateTime = files.DateTime;
		fd->FileSize = files.FileSize;
		fd->PathFileID = files.PathFileID;

		m.insert( FDPair(files.FileName, *fd) );
		delete fd;

		files.DBNextRow();
	}
}

// add a file to the database
void CCatalogVolumeFunctions::AddFileToDB( wxString &path, wxString &fileName, CNullableLong &PathID ) {
	wxFileName fn( path, fileName );
	CFiles file;
	file.FileName = fileName;
	file.FileExt = fn.GetExt();
	if( file.FileExt.Len() > 30 ) file.FileExt = wxEmptyString;	// such a long extension is surely a meaningless temporary file
	file.DateTime = fn.GetModificationTime();
	file.FileSize = fn.GetSize();
	file.PathID = PathID;
	file.PathFileID.SetNull(true);
	file.DbInsert();
	nAddedFiles++;

	if( file.FileExt == wxT("mp3") ) {
		CFilesAudioMetadata metaData;
		if( CAudioMetadata::ReadMP3Metadata( fn.GetFullPath(), metaData ) ) {
			metaData.FileID = file.FileID;
			metaData.DbInsert();
		}
	}
}

void CCatalogVolumeFunctions::AddFolderToDB( wxString &path, wxString &fileName, CNullableLong &PathID, CBaseDB* db, long VolumeID ) {
	wxFileName dirName( path, wxEmptyString );
	dirName.AppendDir( fileName );

	// stores the folder as a file to simplify data retrieval
	CFiles file;
	file.FileName = fileName;
	file.FileExt = wxEmptyString;
	file.DateTime = dirName.GetModificationTime();
	file.FileSize = 0;
	file.PathID = PathID;

	CNullableLong nl;
	nl.SetNull( true );
	CatalogUpdateSingleFolder( db, dirName.GetPath(), VolumeID, nl, PathID, &file );
}

void CCatalogVolumeFunctions::UpdateVolume( wxString volumePath, long volumeID ) {

	// starts a transaction
	CBaseDB* db = CBaseDB::GetDatabase();
	db->TransactionStart();

	wxFileName dirName( volumePath, wxEmptyString );

	// retrieves the id of the root folder
	long rootPathID = -1;
	CPaths pth;
	CNullableLong nl;
	nl.SetNull(true);
	pth.DBStartQueryListPaths( volumeID, nl );
	while( !pth.IsEOF() ) {
		// this query should return only one row
		rootPathID = pth.PathID;
		pth.DBNextRow();
	}

	nUpdatedFiles = nAddedFiles = nDeletedFiles = nDeletedFolders = nUnchangedFiles = 0;

	// catalogs the folders
	CNullableLong FatherID;
	FatherID.SetNull(true);
	CNullableLong nlPathID( rootPathID );
#ifdef __WXMSW__
	CatalogUpdateSingleFolderWindows( db, volumePath, volumeID, nlPathID, FatherID, NULL );
#else
	CatalogUpdateSingleFolder( db, volumePath, volumeID, nlPathID, FatherID, NULL );
#endif

	// update the database statistics, useful after a massive change
	db->UpdateStatistics( CBaseDB::usAll );

	bool doCommit = true;
	if( statText != NULL ) {
		// we are called from a GUI window so we show a report
		wxString msg = _("Number of added files: ") + CUtils::long2string(nAddedFiles) + wxT("\n");
		msg += _("Number of updated files: ") + CUtils::long2string(nUpdatedFiles) + wxT("\n");
		msg += _("Number of deleted files (not counting those in deleted folders): ") + CUtils::long2string(nDeletedFiles) + wxT("\n");
		msg += _("Number of deleted folders: ") + CUtils::long2string(nDeletedFolders) + wxT("\n");
		msg += _("Number of unchanged files: ") + CUtils::long2string(nUnchangedFiles) + wxT("\n") + wxT("\n");
		msg += _("Do you really want to update the volume?");
		doCommit = CUtils::MsgAskYes( msg );
	}

	// commits the transaction
	if( doCommit )
		db->TransactionCommit();
	else
		db->TransactionRollback();

}

