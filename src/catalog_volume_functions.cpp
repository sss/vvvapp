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

	// catalogs the folders
	CNullableLong FatherID;
	FatherID.SetNull(true);
#ifdef __WXMSW__
	CatalogSingleFolderWindows( db, volumePath, vol.VolumeID, FatherID, NULL );
#else
	CatalogSingleFolder( db, volumePath, vol.VolumeID, FatherID, NULL );
#endif

	// commits the transaction
	db->TransactionCommit();
}

void CCatalogVolumeFunctions::CatalogSingleFolder( CBaseDB* db, wxString path, long VolumeID, CNullableLong& FatherID, CFiles* PathFile  ) {
	wxString fileName;

	// shows the path in the dialog box
	if( statText != NULL ) {
		statText->SetLabel( path );
		wxTheApp->Yield();
	}

	// writes the path row
	CNullableLong PathID = WritePathRow( path, VolumeID, FatherID );

	// adds the path id and stores the FILES info about this folder
	if( PathFile != NULL ) {
		PathFile->PathFileID = PathID;
		PathFile->DbInsert();
	}

	// reads all file names
	wxDir dir(path);
	bool cont = dir.GetFirst(&fileName, wxT(""), wxDIR_FILES );
	while( cont ) {
		// stores the file row
		AddFileToDB( path, fileName, PathID );

		cont = dir.GetNext(&fileName);
	}

	// now reads all the subfolders
	cont = dir.GetFirst(&fileName, wxT(""), wxDIR_DIRS );
	while( cont ) {
		AddFolderToDB( path, fileName, PathID, db, VolumeID );
		cont = dir.GetNext(&fileName);
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

		m.insert( FDPair(files.FileName, *fd) );

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

		CatalogSingleFolder( db, dirName.GetPath(), VolumeID, PathID, &file );
}

