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

#include "files.h"

CFiles::CFiles(void) {
	FileName = wxEmptyString;
	FileExt = wxEmptyString;
	FileDescription = wxEmptyString;
}

CFiles::~CFiles(void) {
}

void CFiles::DBStartQueryListFiles( long PathID ) {
	wxString sql = wxT("SELECT * FROM FILES WHERE PATH_ID = ") + CUtils::long2string(PathID) + wxT(" ORDER BY FILE_NAME");
	DBStartMultiRowQuery( sql, true );
}

void CFiles::DBStartSearchVolumeFilesSQL( CNullableLong volumeID, const wxString& wh )
{
	wxString sql;

	if( volumeID.IsNull() ) {
		// all volumes
		sql = wxT("SELECT * FROM FILES WHERE ") + wh;
	}
	else {
		sql = wxT("SELECT FILES.* FROM FILES INNER JOIN PATHS on FILES.PATH_ID = PATHS.PATH_ID WHERE PATHS.VOLUME_ID = ") + CUtils::long2string(volumeID) + wxT(" AND ") + wh;
	}

	DBStartMultiRowQuery( sql, true );
}

void CFiles::DBStartSearchFolderFilesSQL( long folderID, const wxString& wh  )
{
	wxString sql;

	sql = wxT("SELECT * FROM FILES WHERE PATH_ID = ") + CUtils::long2string(folderID) + wxT(" AND ") + wh;

	DBStartMultiRowQuery( sql, true );
}

void CFiles::UpdateDescription( long FileID, const wxString& descr ) {

	switch( DatabaseType ) {
		case dbtFirebird:
			FB_UpdateDescription( FileID, descr );
			break;
	}
}

void CFiles::UpdateDateSize( long FileID, const wxDateTime& fdt, const wxLongLong& fs ) {

	switch( DatabaseType ) {
		case dbtFirebird:
			FB_UpdateDateSize( FileID, fdt, fs );
			break;
	}
}

std::vector<wxString> CFiles::ListFolderExtensions( long PathID )
{
	std::vector<wxString> retVal;
	switch( DatabaseType ) {
		case dbtFirebird:
			retVal = FB_ListFolderExtensions( PathID );
			break;
	}
	return retVal;
}

