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

#include "base_db.h"
#include "base_rec.h"
#include "../firebird/firebird_db.h"

using namespace std;

CBaseDB* CBaseDB::_instance = 0;


void CBaseDB::CreateFirebirdDatabase( wxString serverName, wxString databaseName, wxString userName, wxString password ) {
	if( _instance == 0 ) {
		_instance = new CFirebirdDB( serverName, databaseName, userName, password );
		CBaseRec::SetDatabaseType( CBaseRec::dbtFirebird );
	}
}


void CBaseDB::DeleteFirebirdDatabase(void) {
	if( _instance != 0 ) {
		delete (CFirebirdDB*) _instance;
		_instance = 0;
		CBaseRec::SetDatabaseType( CBaseRec::dbtUndefined );
	}
}


CBaseDB* CBaseDB::GetDatabase(void) {
	return _instance;
}
