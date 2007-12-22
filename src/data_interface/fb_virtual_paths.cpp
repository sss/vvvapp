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

void CVirtualPaths::FB_DbInsert(void) {
	bool inTransaction;
	int64_t tmp;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH( ?, ?, ? )" );
		st->Set( 1, PathName );
		if( FatherID.IsNull() )
			st->SetNull( 2 );
		else
			st->Set( 2, (int32_t) FatherID );
		if( PhysPathID.IsNull() )
			st->SetNull( 3 );
		else
			st->Set( 3, (int32_t) PhysPathID );
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

	// get the ID of the created row
	st->Get( 1, tmp );
	if( tmp < 0 ) {
		db->TransactionRollback();
		throw CDataErrorException( "Duplicate virtual path name", CDataErrorException::ecUnique );
	}
	PathID = tmp;

	if( !inTransaction ) {
		db->TransactionCommit();
	}

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
		sql += CUtils::long2string(FatherID) + ", ";
	sql += "PHYS_PATH_ID = ";
	if( PhysPathID.IsNull() )
		sql += "NULL ";
	else
		sql += CUtils::long2string(PhysPathID) + " ";
	sql += " WHERE PATH_ID = "  + CUtils::long2string(PathID);
	FB_ExecuteQueryNoReturn( sql );
}

void CVirtualPaths::FB_DbDelete(void)
{
	bool inTransaction;
	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_DELETE_VIRTUAL_FOLDER( ? )" );
		st->Set( 1, (int32_t) PathID );
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
		st->Set( 1, (int32_t) PhysicalPathID );
		st->Set( 2, (int32_t) VirtualPathID );
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


void CVirtualPaths::FB_AppendVolume( long VolumeID, long PhysicalPathID, long VirtualPathID ) {
	bool inTransaction;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_ADD_VOLUME_TO_VIRTUALPATH( ?, ?, ? )" );
		st->Set( 1, (int32_t) VolumeID );
		st->Set( 2, (int32_t) PhysicalPathID );
		st->Set( 3, (int32_t) VirtualPathID );
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


void CVirtualPaths::FB_Rename( long VirtualPathID, wxString newName ) {
	bool inTransaction;
	int64_t tmp;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_RENAME_VIRTUALPATH( ?, ? )" );
		st->Set( 1, (int32_t) VirtualPathID );
		st->Set( 2, newName );
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

	// get result status of the stored procedure
	st->Get( 1, tmp );
	if( tmp != 0 ) {
		// the folder name would be duplicated
		db->TransactionRollback();
		throw CDataErrorException( "Duplicate virtual path name", CDataErrorException::ecUnique );
	}

	if( !inTransaction ) {
		db->TransactionCommit();
	}
}

void CVirtualPaths::FB_AddPhysicalFile( long PhysicalFileID, long VirtualPathID ) {
	bool inTransaction;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH( ?, ? )" );
		st->Set( 1, (int32_t) PhysicalFileID );
		st->Set( 2, (int32_t) VirtualPathID );
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




