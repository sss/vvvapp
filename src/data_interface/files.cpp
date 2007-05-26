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

