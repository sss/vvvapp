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

#ifndef __PATHS_H__
#define __PATHS_H__

#include <wx/string.h>

#include "base_rec.h"

using namespace std;

class CPaths : public CBaseRec
{
public:
	CPaths(void);
	~CPaths(void);
	
	// data members ----------------------------
	wxString PathName;
	CNullableLong PathID;
	CNullableLong VolumeID;
	CNullableLong FatherID;
	wxString PathDescription;

	// methods -----------------------------------

	// starts a multirow query that returns all the paths with a given VolumeID and FatherID (nullable)
	void DBStartQueryListPaths( long VolumeID, CNullableLong FatherID );

	// returns the full path
	static wxString GetFullPath( long PathID );

	// updates the decription
	static void UpdateDescription( long PathID, const wxString& descr );


protected:

	// Firebird implementation of the database methods
	void FB_DbInsert(void);
	void FB_DbUpdate(void);
	void FB_DbDelete(void);
	void FB_FetchRow(void);

	static wxString FB_GetFullPath( long PathID );
	static void FB_UpdateDescription( long PathID, const wxString& descr );

};


#endif
