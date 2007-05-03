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

#include <wx/filename.h>

#include "paths.h"
#include "firebird_db.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

// add this record to the database
void CPaths::FB_DbInsert(void)
{
	wxString sql;

	if( PathID.IsNull() )
		PathID = FB_GenNewValue( wxT("GEN_PATHS_ID") );
	sql = "INSERT INTO PATHS (";
	if( !PathID.IsNull() )
		sql += "PATH_ID, ";
	sql += "VOLUME_ID, PATH_NAME, FATHER_ID) VALUES (";
	if( !PathID.IsNull() )
		sql += long2string(PathID) + ", ";
	sql += long2string(VolumeID) + ", '" + ExpandSingleQuotes(PathName) + "', ";
	if( FatherID.IsNull() )
		sql += "NULL";
	else
		sql += long2string(FatherID);
	sql += ")";
	FB_ExecuteQueryNoReturn( sql );
}

void CPaths::FB_DbUpdate(void)
{
	wxString sql;

	sql = "UPDATE PATHS SET ";
	sql += "VOLUME_ID = " + long2string(VolumeID) + ", ";
	sql += "PATH_NAME = '" + ExpandSingleQuotes(PathName) + "', ";
	sql += "FATHER_ID = ";
	if( FatherID.IsNull() )
		sql += "NULL ";
	else
		sql += long2string(FatherID) + " ";
	sql += " WHERE PATH_ID = "  + long2string(PathID);
	FB_ExecuteQueryNoReturn( sql );
}

void CPaths::FB_DbDelete(void)
{
	wxString sql;

	sql = "DELETE FROM PATHS WHERE PATH_ID = " + long2string( PathID );
	FB_ExecuteQueryNoReturn( sql );
}


void CPaths::FB_FetchRow(void) {
	int64_t tmp;
	string stmp;

	if( FB_st->Fetch() ) {
		// fetches a record
		eof = false;
		FB_st->Get( "PATH_NAME", stmp );
		PathName = CUtils::std2wx( stmp );
		FB_st->Get("PATH_ID", tmp);
		PathID = (long) tmp;
		FB_st->Get("VOLUME_ID", tmp);
		VolumeID = (long) tmp;
		if( FB_st->IsNull("FATHER_ID") )
			FatherID.SetNull(true);
		else {
			FB_st->Get("FATHER_ID", tmp);
			FatherID = (long) tmp;
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

wxString CPaths::FB_GetFullPath( long PathID ) {
	bool inTransaction;
	std::string stmp;

	CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
	inTransaction = db->TransactionIsOpened();
	if( !inTransaction ) {
		db->TransactionStart();
	}
	Statement st = StatementFactory( db->GetIBPPDB(), db->TransactionGetReference() );

	st->Prepare( "EXECUTE PROCEDURE SP_GET_FULL_PATH( ?, ? )" );
	st->Set( 1, PathID );
	st->Set( 2, wxString(wxFileName::GetPathSeparator()).c_str() );
	st->Execute();

	if( !inTransaction ) {
		db->TransactionCommit();
	}

	st->Get( 1, stmp );
	return CUtils::std2wx( stmp );

}