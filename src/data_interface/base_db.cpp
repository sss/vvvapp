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
