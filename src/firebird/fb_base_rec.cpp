#include "../data_interface/base_rec.h"
#include "../firebird/firebird_db.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

// executes a query that does not return rows
void CBaseRec::FB_ExecuteQueryNoReturn( wxString sql ) {
	bool inTransaction;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );
	st->Execute( CUtils::wx2std(sql) );
	if( !inTransaction ) {
		db->TransactionCommit();
	}
}


// this function will always start a new transaction, so it cannot be called
// from inside a transaction
void CBaseRec::FB_DBStartMultiRowQuery( wxString sql, bool readOnly ) {
	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	db->TransactionStart( readOnly );
	FB_st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );
	FB_st->Execute( CUtils::wx2std(sql) );
	FB_FetchRow();
}

void CBaseRec::FB_DBNextRow(void) {
	FB_FetchRow();
}

// returns a new value from a generator
long CBaseRec::FB_GenNewValue( wxString generatorName ) {
	bool inTransaction;	// true if a transaction has already been started
	wxString sql;
	int64_t tmp;
	long retVal;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();

	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart( true );
	}
	
	sql = "SELECT GEN_ID(" + generatorName + ", 1) AS NEW_ID FROM RDB$DATABASE";
	FB_st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );
	FB_st->Execute( CUtils::wx2std(sql) );
	if( FB_st->Fetch() ) {
		FB_st->Get("NEW_ID", tmp);
		retVal = (long) tmp;
	}
	else
		retVal = -1;

	if( !inTransaction ) {
		db->TransactionCommit();
	}

	return retVal;
}

bool CBaseRec::FB_QueryReturnsNoRows( wxString sql ) {
	bool inTransaction, retVal;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}

	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );
	st->Execute( CUtils::wx2std(sql) );
	retVal = !st->Fetch();

	if( !inTransaction ) {
		db->TransactionCommit();
	}

	return retVal;
}