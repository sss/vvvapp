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

#include "firebird_db.h"

using namespace IBPP;

CFirebirdDB::CFirebirdDB( wxString serverName, wxString databaseName, wxString userName, wxString password )
{
	this->serverName = serverName;
	this->databaseName = databaseName;
	this->userName = userName;
	this->password = password;

	db = DatabaseFactory( CUtils::wx2std(serverName), CUtils::wx2std(databaseName), CUtils::wx2std(userName), CUtils::wx2std(password) );
	tr = NULL;
}

CFirebirdDB::~CFirebirdDB(void)
{
}

wxString CFirebirdDB::Connect(void) {
	wxString msgErr;
	try {
		db->Connect();
		msgErr.Empty();
	}
	catch( Exception& e ) {
		msgErr = e.ErrorMessage();
	}
	return msgErr;
}


void CFirebirdDB::Disconnect(void) {
	db->Disconnect();
}

void CFirebirdDB::TransactionStart( bool readOnly ) {
	tr = TransactionFactory( db, readOnly ? amRead : amWrite );
	tr->Start();
}

void CFirebirdDB::TransactionCommit(void) {
	tr->Commit();
	tr = NULL;
}

void CFirebirdDB::TransactionRollback(void) {
	tr->Rollback();
	tr = NULL;
}

bool CFirebirdDB::TransactionIsOpened(void) {
	return (tr != NULL);
}

