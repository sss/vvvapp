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

void CFirebirdDB::CreateDatabaseOnDisk( wxString serverName, wxString userName, wxString password, wxString backupName, wxString databaseName ) {

	Service svc = ServiceFactory( CUtils::wx2std(serverName), CUtils::wx2std(userName), CUtils::wx2std(password) );
	svc->Connect();
	svc->StartRestore( CUtils::wx2std(backupName), CUtils::wx2std(databaseName), 4096 );
	svc->Wait();
	svc->Disconnect();
}

int CFirebirdDB::GetDatabaseVersion(void) {
	int64_t tmp;

	TransactionStart();
	Statement st = StatementFactory( GetIBPPDB(), TransactionGetReference() );
	st->Prepare( "SELECT DB_VERSION FROM SERVICE WHERE SERVICE_ID = 1" );
	st->Execute();
	st->Fetch();
	st->Get( "DB_VERSION", tmp );
	TransactionCommit();

	return tmp;
}

void CFirebirdDB::UpgradeDatabase( int currentVersion ) {

	// opens the database containing the metadata changes and reads them
	Database upgDb = DatabaseFactory( CUtils::wx2std(serverName), CUtils::wx2std(CUtils::GetStructUpdateDbName()), CUtils::wx2std(userName), CUtils::wx2std(password) );
	upgDb->Connect();
	Transaction upgTr = TransactionFactory( upgDb );
	upgTr->Start();
	wxString sql = "SELECT VERSION_NUMBER, SCRIPT_CODE FROM UPDATE_SCRIPTS WHERE VERSION_NUMBER > " + CUtils::long2string(currentVersion) + " ORDER BY VERSION_NUMBER";
	Statement stUpg = StatementFactory( upgDb, upgTr );
	stUpg->Execute( CUtils::wx2std(sql) );
	wxArrayString scripts;
	int finalVersion = 0;
	while( stUpg->Fetch() ) {
		string s;
		stUpg->Get( "VERSION_NUMBER", finalVersion );
		stUpg->Get( "SCRIPT_CODE", s );
		scripts.Add( CUtils::std2wx(s) );
	}
	upgTr->Commit();
	upgDb->Disconnect();

	wxASSERT( finalVersion > currentVersion );

	// now "scripts" contains all the scripts that must be executed to upgrade the current database

	// execute all the scripts
	TransactionStart();
	Statement st = StatementFactory( GetIBPPDB(), TransactionGetReference() );
	for( int k = 0; k < (int) scripts.GetCount(); k ++ ) {
		st->ExecuteImmediate( CUtils::wx2std(scripts[k]) );
	}
	sql = "UPDATE SERVICE SET DB_VERSION = " + CUtils::long2string(finalVersion) + "WHERE SERVICE_ID = 1";
	st->ExecuteImmediate( CUtils::wx2std(sql) );
	TransactionCommit();

}