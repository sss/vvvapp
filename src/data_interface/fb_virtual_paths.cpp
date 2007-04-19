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

#include "data_error.h"
#include "virtual_paths.h"
#include "firebird_db.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

// add this record to the database
void CVirtualPaths::FB_DbInsert(void)
{
	wxString sql;

	if( PathID.IsNull() )
		PathID = FB_GenNewValue( wxT("GEN_VIRTUAL_PATHS_ID") );
	sql = "INSERT INTO VIRTUAL_PATHS (";
	if( !PathID.IsNull() )
		sql += "PATH_ID, ";
	sql += "PATH, FATHER_ID, PHYS_PATH_ID) VALUES (";
	if( !PathID.IsNull() )
		sql += long2string(PathID) + ", ";
	sql += ExpandSingleQuotes(PathName) + "', ";
	if( FatherID.IsNull() )
		sql += "NULL";
	else
		sql += long2string(FatherID);
	sql += "', ";
	if( PhysPathID.IsNull() )
		sql += "NULL";
	else
		sql += long2string(PhysPathID);
	sql += ")";
	FB_ExecuteQueryNoReturn( sql );
}

void CVirtualPaths::FB_DbUpdate(void)
{
	wxString sql;

	sql = "UPDATE PATHS SET ";
	sql += "PATH = '" + ExpandSingleQuotes(PathName) + "', ";
	sql += "FATHER_ID = ";
	if( FatherID.IsNull() )
		sql += "NULL, ";
	else
		sql += long2string(FatherID) + ", ";
	sql += "PHYS_PATH_ID = ";
	if( PhysPathID.IsNull() )
		sql += "NULL ";
	else
		sql += long2string(PhysPathID) + " ";
	sql += " WHERE PATH_ID = "  + long2string(PathID);
	FB_ExecuteQueryNoReturn( sql );
}

void CVirtualPaths::FB_DbDelete(void)
{
	wxString sql;

	sql = "DELETE FROM VIRTUAL_PATHS WHERE PATH_ID = " + long2string( PathID );
	FB_ExecuteQueryNoReturn( sql );
}


void CVirtualPaths::FB_FetchRow(void) {
	int64_t tmp;
	string stmp;

	if( FB_st->Fetch() ) {
		// fetches a record
		eof = false;
		FB_st->Get( "PATH", stmp );
		PathName = CUtils::std2wx( stmp );
		FB_st->Get("PATH_ID", tmp);
		PathID = (long) tmp;
		if( FB_st->IsNull("FATHER_ID") )
			FatherID.SetNull(true);
		else {
			FB_st->Get("FATHER_ID", tmp);
			FatherID = (long) tmp;
		}
		if( FB_st->IsNull("PHYS_PATH_ID") )
			PhysPathID.SetNull(true);
		else {
			FB_st->Get("PHYS_PATH_ID", tmp);
			PhysPathID = (long) tmp;
		}
	}
	else {
		// end of the rowset
		eof = true;
		if( !TransactionAlreadyStarted ) {
			CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
			db->TransactionCommit();
		}
		TransactionAlreadyStarted = false;
	}
}

void CVirtualPaths::FB_AppendPhysicalPath( long PhysicalPathID, long VirtualPathID ) {
	bool inTransaction;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_APPEND_PHYSPTH_TO_VIRTUALPTH( ?, ? )" );
		st->Set( 1, PhysicalPathID );
		st->Set( 2, VirtualPathID );
		st->Execute();
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


void CVirtualPaths::FB_CopyPhysicalPath( long PhysicalPathID, long VirtualPathID ) {
	bool inTransaction;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_ADD_PHYSPATH_TO_VIRTUALPATH( ?, ? )" );
		st->Set( 1, PhysicalPathID );
		st->Set( 2, VirtualPathID );
		st->Execute();
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
