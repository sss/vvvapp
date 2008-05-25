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

#include "base_rec.h"
#include "data_error.h"
#include "firebird_db.h"
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

	try {
		st->Execute( CUtils::DBwx2std(sql) );
	}
	catch( IBPP::SQLException& e ) {
		// catches exceptions in order to convert interesting ones
		db->TransactionRollback();
		CDataErrorException::ErrorCause ec;
		if( CDataErrorException::ConvertFirebirdError( e.EngineCode(), ec )  )
			throw CDataErrorException( e.ErrorMessage(), ec );
		else
			throw;
	}

	if( !inTransaction ) {
		db->TransactionCommit();
	}
}


// this function will always start a new transaction, so it cannot be called
// from inside a transaction
void CBaseRec::FB_DBStartMultiRowQuery( wxString sql, bool readOnly ) {
	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	TransactionAlreadyStarted = db->TransactionIsOpened();
	if( !TransactionAlreadyStarted )
		db->TransactionStart( readOnly );
	FB_st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );
	FB_st->Execute( CUtils::DBwx2std(sql) );
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
	
	sql = wxT("SELECT GEN_ID(") + generatorName + wxT(", 1) AS NEW_ID FROM RDB$DATABASE");
	FB_st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );
	FB_st->Execute( CUtils::DBwx2std(sql) );
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
	st->Execute( CUtils::DBwx2std(sql) );
	retVal = !st->Fetch();

	if( !inTransaction ) {
		db->TransactionCommit();
	}

	return retVal;
}
