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

#ifndef __VIRTUAL_FILES_H__
#define __VIRTUAL_FILES_H__

#include <wx/string.h>
#include "wx/datetime.h"
#include "base_rec.h"

using namespace std;

class CVirtualFiles : public CBaseRec
{
public:
	CVirtualFiles(void);
	~CVirtualFiles(void);
	
	// data members ----------------------------
	CNullableLong FileID;
	long VirtualPathID;
	long PhysicalFileID;
	CNullableLong VirtualPathFileID;

	// data from the referenced physical file. Only filled by queries
	wxString FileName;
	wxString FileExt;
	wxDateTime DateTime;
	wxLongLong FileSize;
	CNullableLong PhysicalPathID;
	CNullableLong PathFileID;
	wxString FullPhysicalPath;	// the full physical path to this file
	wxString FileDescription;

	// methods -----------------------------------

	// starts a multirow query that returns all the files from a given VirtualPathID
	// always returns a join between VIRTUAL_FILES and FILES
	void DBStartQueryListFiles( long VirtualPathID );

	// searches all the files in a folder and its subfolders
	void DBStartSearchFolderFiles( wxString fileName, bool useFileNameWildcards, wxString ext, wxString description, bool useDescriptionWildcards, long folderID );

	// true if this row represents a folder
	bool IsFolder(void) { return !VirtualPathFileID.IsNull(); }

	// return a vector containing all the extensions found in a folder
	static std::vector<wxString> ListFolderExtensions( long PathID );

protected:

	// Firebird implementation of the database methods
	void FB_DbInsert(void);
	void FB_DbUpdate(void);
	void FB_DbDelete(void);
	void FB_FetchRow(void);
	static std::vector<wxString> FB_ListFolderExtensions( long PathID );

};


#endif
