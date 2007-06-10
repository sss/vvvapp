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
	FileName = "";
	FileExt = "";
}

CFiles::~CFiles(void) {
}

void CFiles::DBStartQueryListFiles( long PathID ) {
	wxString sql = "SELECT * FROM FILES WHERE PATH_ID = " + CUtils::long2string(PathID) + " ORDER BY FILE_NAME";
	DBStartMultiRowQuery( sql, true );
}

void CFiles::DBStartSearchVolumeFiles( wxString fileName, bool useFileNameWildcards, wxString ext, CNullableLong volumeID ) {
	wxString sql;

	fileName = fileName.MakeUpper();
	ext = ext.MakeUpper();

	if( volumeID.IsNull() ) {
		// all volumes
		sql = "SELECT * FROM FILES WHERE PATH_FILE_ID IS NULL";
		if( !fileName.empty() && useFileNameWildcards )
			sql += " AND UPPER(FILE_NAME) LIKE '" + fileName + "' ESCAPE '/'";
		if( !fileName.empty() && !useFileNameWildcards )
			sql += " AND UPPER(FILE_NAME) = '" + fileName + "'";
		if( !ext.empty() )
			sql += " AND UPPER(FILE_EXT) = '" + ExpandSingleQuotes(ext) + "'";
	}
	else {
		sql = "SELECT FILES.* FROM FILES INNER JOIN PATHS on FILES.PATH_ID = PATHS.PATH_ID WHERE PATH_FILE_ID IS NULL AND PATHS.VOLUME_ID = " + CUtils::long2string(volumeID);
		if( !fileName.empty() && useFileNameWildcards )
			sql += " AND UPPER(FILE_NAME) LIKE '" + fileName + "' ESCAPE '/'";
		if( !fileName.empty() && !useFileNameWildcards )
			sql += " AND UPPER(FILE_NAME) = '" + fileName + "'";
		if( !ext.empty() )
			sql += " AND UPPER(FILE_EXT) = '" + ExpandSingleQuotes(ext) + "'";
	}

	DBStartMultiRowQuery( sql, true );

}

void CFiles::DBStartSearchFolderFiles( wxString fileName, bool useFileNameWildcards, wxString ext, long folderID ) {
	wxString sql;

	fileName = fileName.MakeUpper();
	ext = ext.MakeUpper();

	sql = "SELECT * FROM FILES WHERE PATH_FILE_ID IS NULL AND PATH_ID = " + CUtils::long2string(folderID);
	if( !fileName.empty() && useFileNameWildcards )
		sql += " AND UPPER(FILE_NAME) LIKE '" + fileName + "' ESCAPE '/'";
	if( !fileName.empty() && !useFileNameWildcards )
		sql += " AND UPPER(FILE_NAME) = '" + fileName + "'";
	if( !ext.empty() )
		sql += " AND UPPER(FILE_EXT) = '" + ExpandSingleQuotes(ext) + "'";

	DBStartMultiRowQuery( sql, true );

}

