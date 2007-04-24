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

#include "files.h"
#include "firebird_db.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

// add this record to the database
void CFiles::FB_DbInsert(void)
{
	wxString sql;

	sql = "INSERT INTO FILES (";
	if( !FileID.IsNull() )
		sql += "FILE_ID, ";
	sql += "FILE_NAME, FILE_EXT, FILE_SIZE, FILE_DATETIME, PATH_FILE_ID, PATH_ID) VALUES (";
	if( !FileID.IsNull() )
		sql += long2string(FileID) + ", ";
	sql += "'" + ExpandSingleQuotes(FileName) + "', '" + 
		         ExpandSingleQuotes(FileExt) + "', " + 
                 FileSize.ToString() + ", " +
				 DateTime.Format( "'%Y-%m-%d %H:%M:%S'" ) + ", " +
				 (PathFileID.IsNull() ? "NULL" : long2string(PathFileID) ) + ", " +
				 long2string(PathID) + ")";
	FB_ExecuteQueryNoReturn( sql );
}

void CFiles::FB_DbUpdate(void)
{
// not used (and not working)

	//wxString sql;

	//sql = "UPDATE FILES SET ";
	//sql += "FILE_NAME = '" + ExpandSingleQuotes(FileName) + "', ";
	//sql += "FILE_EXT = '" + ExpandSingleQuotes(FileExt) + "', ";
	//sql += "FILE_SIZE = " + FileSize.ToString() + ", ";
	//sql += "FILE_DATETIME = " + DateTime.Format( "'%Y-%m-%d %H:%M:%S'" ) + ", ";
	//sql += "IS_FOLDER = '";
	//sql += "', ";
	//sql += "IS_FOLDER = '" + wxString(IsFolder ? "T" : "F") + "', ";
	//sql += "PATH_ID = " + long2string(PathID) + " ";
	//sql += "WHERE FILE_ID = "  + long2string(FileID);
	//FB_ExecuteQueryNoReturn( sql );
}

void CFiles::FB_DbDelete(void)
{
	wxString sql;

	sql = "DELETE FROM FILES WHERE FILE_ID = " + long2string( FileID );
	FB_ExecuteQueryNoReturn( sql );
}


void CFiles::FB_FetchRow(void) {
	int64_t tmp;
	string stmp;
	Timestamp ts;

	if( FB_st->Fetch() ) {
		// fetches a record
		eof = false;
		FB_st->Get("FILE_ID", tmp);
		FileID = (long) tmp;
		FB_st->Get( "FILE_NAME", stmp );
		FileName = CUtils::std2wx( stmp );
		FB_st->Get( "FILE_EXT", stmp );
		FileExt = CUtils::std2wx( stmp );
		FB_st->Get("FILE_SIZE", tmp);
		FileSize = (long) tmp;
		FB_st->Get("FILE_DATETIME", ts);
		DateTime.Set( ts.Day(), (wxDateTime::Month) (wxDateTime::Jan + ts.Month() - 1), ts.Year(), ts.Hours(), ts.Minutes(), ts.Seconds() );
		if( FB_st->IsNull("PATH_FILE_ID") )
			PathFileID.SetNull(true);
		else {
			FB_st->Get("PATH_FILE_ID", tmp);
			PathFileID = (long) tmp;
		}
		FB_st->Get("PATH_ID", tmp);
		PathID = (long) tmp;
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