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

#include "virtual_files.h"
#include "firebird_db.h"
#include "paths.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

// add this record to the database
void CVirtualFiles::FB_DbInsert(void)
{
	wxString sql;

	sql = wxT("INSERT INTO VIRTUAL_FILES (");
	if( !FileID.IsNull() )
		sql += wxT("FILE_ID, ");
	sql += wxT("VIRTUAL_PATH_ID, PHYSICAL_FILE_ID) VALUES (");
	if( !FileID.IsNull() )
		sql += CUtils::long2string(FileID) + wxT(", ");
	sql += CUtils::long2string(VirtualPathID) + wxT(", ") + 
		   CUtils::long2string(PhysicalFileID) + wxT(")");
	FB_ExecuteQueryNoReturn( sql );
}

void CVirtualFiles::FB_DbUpdate(void)
{
	wxString sql;

	sql = wxT("UPDATE VIRTUAL_FILES SET ");
	sql += wxT("VIRTUAL_PATH_ID = ") + CUtils::long2string(VirtualPathID) + wxT(", ");
	sql += wxT("PHYSICAL_FILE_ID = ") + CUtils::long2string(PhysicalFileID) + wxT(" ");
	sql += wxT("WHERE FILE_ID = ") + CUtils::long2string(FileID);
	FB_ExecuteQueryNoReturn( sql );
}

void CVirtualFiles::FB_DbDelete(void)
{
	wxString sql;

	sql = wxT("DELETE FROM VIRTUAL_FILES WHERE FILE_ID = ") + CUtils::long2string( FileID );
	FB_ExecuteQueryNoReturn( sql );
}


void CVirtualFiles::FB_FetchRow(void) {
	int64_t tmp;
	string stmp;
	Timestamp ts;

	if( FB_st->Fetch() ) {
		// fetches a record
		eof = false;
		FB_st->Get("FILE_ID", tmp);
		FileID = (long) tmp;
		FB_st->Get("VIRTUAL_PATH_ID", tmp);
		VirtualPathID = (long) tmp;
		FB_st->Get("PHYSICAL_FILE_ID", tmp);
		PhysicalFileID = (long) tmp;

		FB_st->Get( "FILE_NAME", stmp );
		FileName = CUtils::std2wx( stmp );
		FB_st->Get( "FILE_EXT", stmp );
		FileExt = CUtils::std2wx( stmp );
		FB_st->Get("FILE_SIZE", tmp);
		FileSize = (wxLongLong) tmp;
		FB_st->Get("FILE_DATETIME", ts);
		DateTime.Set( ts.Day(), (wxDateTime::Month) (wxDateTime::Jan + ts.Month() - 1), ts.Year(), ts.Hours(), ts.Minutes(), ts.Seconds() );
		if( FB_st->IsNull("VIRTUAL_PATH_FILE_ID") )
			VirtualPathFileID.SetNull(true);
		else {
			FB_st->Get("VIRTUAL_PATH_FILE_ID", tmp);
			VirtualPathFileID = (long) tmp;
		}
		if( FB_st->IsNull("PATH_FILE_ID") )
			PathFileID.SetNull(true);
		else {
			FB_st->Get("PATH_FILE_ID", tmp);
			PathFileID = (long) tmp;
		}
		FB_st->Get("PATH_ID", tmp);
		PhysicalPathID = (long) tmp;
		if( FB_st->IsNull("FILE_DESCRIPTION") ) {
			FileDescription = wxEmptyString;
		}
		else {
			FB_st->Get( "FILE_DESCRIPTION", stmp );
			FileDescription = CUtils::std2wx( stmp );
		}
		FullPhysicalPath = CPaths::GetFullPath( PhysicalPathID );
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
