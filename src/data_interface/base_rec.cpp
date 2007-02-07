/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2007, the VVV Development team

	Author: Fulvio Senore

    VVV is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VVV; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "base_rec.h"

CBaseRec::CBaseRec(void)
{
	TransactionAlreadyStarted = false;
}

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
	wxString retVal;
	retVal.Printf( "%d", val );
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
