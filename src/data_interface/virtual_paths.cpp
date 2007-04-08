/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2007, the VVV Development team

	Author: Fulvio Senore

    VVV is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VVV; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "virtual_paths.h"

CVirtualPaths::CVirtualPaths(void) {
	PathName = "";
}

CVirtualPaths::~CVirtualPaths(void) {
}


void CVirtualPaths::DBStartQueryListPaths( CNullableLong FathID ) {
	wxString sql;

	if( FathID.IsNull() )
		sql = "SELECT * FROM VIRTUAL_PATHS WHERE FATHER_ID IS NULL ORDER BY PATH";
	else
		sql = "SELECT * FROM VIRTUAL_PATHS WHERE FATHER_ID = " + long2string(FathID) + " ORDER BY PATH";

	DBStartMultiRowQuery( sql, true );
}
