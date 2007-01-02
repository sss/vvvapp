#include "../data_interface/files.h"
#include "../firebird/firebird_db.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

// add this record to the database
void CFiles::FB_DbInsert(void)
{
	wxString sql;

	sql = "INSERT INTO FILES (";
	if( !FileID.IsNull() )
		sql += "FILE_ID, ";
	sql += "FILE_NAME, FILE_EXT, FILE_SIZE, FILE_DATETIME, IS_FOLDER, PATH_ID) VALUES (";
	if( !FileID.IsNull() )
		sql += long2string(FileID) + ", ";
	sql += "'" + ExpandSingleQuotes(FileName) + "', '" + 
		         ExpandSingleQuotes(FileExt) + "', " + 
                 FileSize.ToString() + ", " +
				 DateTime.Format( "'%Y-%m-%d %H:%M:%S'" ) + ", '" +
				 (IsFolder ? "T" : "F") + "', " +
				 long2string(PathID) + ")";
	FB_ExecuteQueryNoReturn( sql );
}

void CFiles::FB_DbUpdate(void)
{
	wxString sql;

	sql = "UPDATE FILES SET ";
	sql += "FILE_NAME = '" + ExpandSingleQuotes(FileName) + "', ";
	sql += "FILE_EXT = '" + ExpandSingleQuotes(FileExt) + "', ";
	sql += "FILE_SIZE = " + FileSize.ToString() + ", ";
	sql += "FILE_DATETIME = " + DateTime.Format( "'%Y-%m-%d %H:%M:%S'" ) + ", ";
	sql += "IS_FOLDER = '";
	sql += "', ";
	sql += "IS_FOLDER = '" + wxString(IsFolder ? "T" : "F") + "', ";
	sql += "PATH_ID = " + long2string(PathID) + " ";
	sql += "WHERE FILE_ID = "  + long2string(FileID);
	FB_ExecuteQueryNoReturn( sql );
}

void CFiles::FB_DbDelete(void)
{
	wxString sql;

	sql = "DELETE FROM FILESS WHERE FILE_ID = " + long2string( FileID );
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
		FB_st->Get("IS_FOLDER", stmp);
		FileSize = (stmp == "T");
		FB_st->Get("PATH_ID", tmp);
		PathID = (long) tmp;
	}
	else {
		// end of the rowset
		eof = true;
		CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
		db->TransactionCommit();
	}
}