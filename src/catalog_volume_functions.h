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

/*
this class contains the code used to catalog a volume
*/


#ifndef _CATALOG_VOLUME_FUNCTIONS_H_
#define _CATALOG_VOLUME_FUNCTIONS_H_

#include <map>
#include <wx/stattext.h>

#include "data_interface/base_db.h"
#include "data_interface/db_null.h"
#include "data_interface/files.h"
	
class CCatalogVolumeFunctions
{
public:
	CCatalogVolumeFunctions( wxStaticText *statText );
	~CCatalogVolumeFunctions(void);

	// catalog a volume that is not already stored in the database
	void CatalogVolume( wxString volumePath, wxString volumeName );

	// update a volume already in the database, adding new files and so on...
	void UpdateVolume( wxString volumePath, long volumeID );

private:

	// data about each file already cataloged in the db
	// used when updating a volume to know what has changed
	struct CFileData {
		
		CFileData() { IsStillThere = false; }
		
//		wxString FileName;
		long FileID;
		CNullableLong PathFileID;
		wxDateTime DateTime;
		wxLongLong FileSize;
		bool IsStillThere;	// true if after a volume directory scan the file has been found
		bool IsFolder;	// true if this is a folder, false if it is a file
	};

	typedef pair <wxString, CFileData> FDPair;

	// catalogs the files in a folder and recursively
	// calls itself for each subfolder
	// PathFile contains the data of the file that will store data about the current folder (if not NULL)
	//   each instance of this method will add the ID of the path and it will save it in the database
//	void CatalogSingleFolder( CBaseDB* db, wxString path, long VolumeID, CNullableLong& FatherID, CFiles* PathFile  );

	void CatalogUpdateSingleFolder( CBaseDB* db, wxString path, long VolumeID, CNullableLong PathID, CNullableLong& FatherID, CFiles* PathFile  );

	// add a file to the database
	void AddFileToDB( wxString &path, wxString &fileName, CNullableLong &PathID );

	// add a folder to the database
	// called by CatalogSingleFolder(), calls again CatalogSingleFolder() recursively
	void AddFolderToDB( wxString &path, wxString &fileName, CNullableLong &PathID, CBaseDB* db, long VolumeID );

#ifdef __WXMSW__
	// Windows-specific version because the standard one was rather slow
	// path: the path to the current folder (the one to be analyzed by the function)
	// VolumeID: the ID of the volume the contains the folder
	// if PathID is null catalog the folder, otherwise update it
	// PathID: the ID of the current folder if we must update it
	// FatherID: the ID of the folder that contains the current folder
	void CatalogUpdateSingleFolderWindows( CBaseDB* db, wxString path, long VolumeID, CNullableLong PathID, CNullableLong& FatherID, CFiles* PathFile  );
	// add a folder to the database
	// called by CatalogSingleFolderWindows(), calls again CatalogSingleFolderWindows() recursively
	void AddFolderToDBWindows( _tfinddata_t &c_file, wxString &path, CNullableLong &PathID, CBaseDB* db, long VolumeID );
#endif

	// add the PATH row in the database
	// returns the ID if the added row
	long WritePathRow( wxString path, long VolumeID, CNullableLong& FatherID );

	// store the files or folders already presnt in the database into a map object
	void ReadFolderFilesFromDB( map<wxString, CFileData> &m, long pathID );

	// pointer to the static text that will be updated to give some feedback to the user
	// it can be NULL
	wxStaticText *statText;

	// data used when updating a volume
	long nUpdatedFiles;		// number of files that have been updated
	long nAddedFiles;		// number of files that have been added
	long nDeletedFiles;		// number of files that have been deleted
	long nUnchangedFiles;	// number of files that have not been changed

};



#endif
