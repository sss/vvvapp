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

