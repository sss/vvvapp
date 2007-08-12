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

#ifndef __FILES_H__
#define __FILES_H__

#include <wx/string.h>
#include "wx/datetime.h"
#include "base_rec.h"

using namespace std;

class CFiles : public CBaseRec
{
public:
	CFiles(void);
	~CFiles(void);
	
	// data members ----------------------------
	wxString FileName;
	wxString FileExt;
	CNullableLong FileID;
	wxDateTime DateTime;
	wxLongLong FileSize;
	long PathID;
	CNullableLong PathFileID;
	wxString FileDescription;

	// methods -----------------------------------

	// starts a multirow query that returns all the files from a given PathID
	void DBStartQueryListFiles( long PathID );

	// true if this row represents a folder
	bool IsFolder(void) { return !PathFileID.IsNull(); }

	// searches all the files of a given volume
	// if volumeID is null searches all the stored volumes
	// if useFileNameWildcards == true the file name contains wildcards, fileName wildcards must already be escaped
	void DBStartSearchVolumeFiles( wxString fileName, bool useFileNameWildcards, wxString ext, CNullableLong volumeID );

	// searches all the files in a folder and its subfolders
	void DBStartSearchFolderFiles( wxString fileName, bool useFileNameWildcards, wxString ext, long folderID );

	// updates the decription
	static void UpdateDescription( long FileID, const wxString& descr );

protected:

	// Firebird implementation of the database methods
	void FB_DbInsert(void);
	void FB_DbUpdate(void);
	void FB_DbDelete(void);
	void FB_FetchRow(void);

	static void FB_UpdateDescription( long FileID, const wxString& descr );
};


#endif
