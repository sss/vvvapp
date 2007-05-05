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
#include "volumes.h"
#include "firebird_db.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

// add this record to the database
void CVolumes::FB_DbInsert(void)
{
	wxString sql;

	if( VolumeID.IsNull() )
		VolumeID = FB_GenNewValue( wxT("GEN_VOLUMES_ID") );
	sql = "INSERT INTO VOLUMES (VOLUME_ID, VOLUME_NAME) VALUES (" +  long2string(VolumeID) + ", '" + ExpandSingleQuotes(VolumeName) + "')";
	FB_ExecuteQueryNoReturn( sql );
}

// update this record into the database
void CVolumes::FB_DbUpdate(void)
{
	wxString sql;

	sql = "UPDATE VOLUMES SET VOLUME_NAME = '" + ExpandSingleQuotes(VolumeName) + "' WHERE VOLUME_ID = " + long2string( VolumeID );
	FB_ExecuteQueryNoReturn( sql );
}


// delete this record from the database
void CVolumes::FB_DbDelete(void)
{
	bool inTransaction;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	try {
		st->Prepare( "EXECUTE PROCEDURE SP_DELETE_VOLUME( ? )" );
		st->Set( 1, VolumeID );
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

void CVolumes::FB_FetchRow(void) {
	int64_t tmp;
	string stmp;

	if( FB_st->Fetch() ) {
		// fetches a record
		eof = false;
		FB_st->Get( "VOLUME_NAME", stmp );
		VolumeName = CUtils::std2wx( stmp );
		if( FB_st->IsNull("VOLUME_ID") )
			VolumeID.SetNull(true);
		else {
			FB_st->Get("VOLUME_ID", tmp);
			VolumeID = (long) tmp;
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

bool CVolumes::FB_NameExists(void) {
	wxString sql;

	sql = "SELECT VOLUME_ID FROM VOLUMES WHERE VOLUME_NAME = '" + ExpandSingleQuotes(VolumeName) + "'";
	return !FB_QueryReturnsNoRows( sql );
}

