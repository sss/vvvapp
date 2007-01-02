#include "base_rec.h"

//CBaseRec::CBaseRec(void)
//{
//}
//
//CBaseRec::~CBaseRec(void)
//{
//}

CBaseRec::DBType CBaseRec::DatabaseType = dbtUndefined;

// add this record to the database
void CBaseRec::DbInsert(void) {
	switch( DatabaseType ) {
		case dbtFirebird:
			FB_DbInsert();
			break;
	}
}

// update this record into the database
void CBaseRec::DbUpdate(void) {
	switch( DatabaseType ) {
		case dbtFirebird:
			FB_DbUpdate();
			break;
	}
}

// delete this record from the database
void CBaseRec::DbDelete(void) {
	switch( DatabaseType ) {
		case dbtFirebird:
			FB_DbDelete();
			break;
	}
}

void CBaseRec::SetDatabaseType( DBType dbt ) {
	DatabaseType = dbt;
}


wxString CBaseRec::ExpandSingleQuotes( wxString txt ) {
	// doubles single-quote charachters in a string, used to create SQL statements
//	wxString retVal;

	txt.Replace( "'", "''", true );
	return txt;
	//size_t i;

	//retVal = txt;
	//i = 0;
	//while( (i = retVal.Find( "'", i )) != string::npos ) {
	//	retVal.insert( i, "'" );
	//	i += 2;
	//}
//	return retVal;
}



// converts a long to a string
wxString CBaseRec::long2string( long val ) {
	char buf[30];
	wxString retVal = ltoa( val, buf, 10 );
	return retVal;
}


void CBaseRec::DBStartMultiRowQuery( wxString sql, bool readOnly ) {
	switch( DatabaseType ) {
		case dbtFirebird:
			FB_DBStartMultiRowQuery( sql, readOnly );
			break;
	}
}

void CBaseRec::DBNextRow(void) {
	switch( DatabaseType ) {
		case dbtFirebird:
			FB_DBNextRow();
			break;
	}
}
