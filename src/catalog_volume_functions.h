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

#include <wx/stattext.h>

#include "data_interface/base_db.h"
#include "data_interface/db_null.h"
#include "data_interface/files.h"
	
class CCatalogVolumeFunctions
{
public:
	CCatalogVolumeFunctions( wxStaticText *statText );
	~CCatalogVolumeFunctions(void);

	void CatalogVolume( wxString volumePath, wxString volumeName );

private:

	// catalogs the files in a folder and recursively
	// calls itself for each subfolder
	// PathFile contains the data of the file that will store data about the current folder (if not NULL)
	//   each instance of this method will add the ID of the path and it will save it in the database
	void CatalogSingleFolder( CBaseDB* db, wxString path, long VolumeID, CNullableLong& FatherID, CFiles* PathFile  );

#ifdef __WXMSW__
	// Windows-specific version because the standard one was rather slow
	void CatalogSingleFolderWindows( CBaseDB* db, wxString path, long VolumeID, CNullableLong& FatherID, CFiles* PathFile  );
#endif

	// pointer to the static text that will be updated to give some feedback to the user
	// it can be NULL
	wxStaticText *statText;
//	wxWindow *window;

};



#endif
