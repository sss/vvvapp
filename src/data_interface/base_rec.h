#ifndef __BASE_REC_H__
#define __BASE_REC_H__

#include "db_null.h"
#include "base_db.h"
#include "../ibpp/core/ibpp.h"

class CBaseRec
{
friend class CBaseDB;
protected:
	// supported databases
	enum DBType { dbtUndefined, dbtFirebird };
	static DBType DatabaseType;

	// sets the correct database type
	static void SetDatabaseType( DBType dbt );

	// doubles single-quote charachters in a string, used to create SQL statements
	wxString ExpandSingleQuotes( wxString txt );

	// converts a long to a string
	wxString long2string( long val );

	// true if we are past the end of the result set
	bool eof;

	// Firebird specific
	virtual void FB_DbInsert(void) = 0;
	virtual void FB_DbUpdate(void) = 0;
	virtual void FB_DbDelete(void) = 0;
	// executes a query that does not return rows
	void FB_ExecuteQueryNoReturn( wxString sql );
	// current statement, used to manrain state between calls for multi row queries
	IBPP::Statement FB_st;
	void FB_DBStartMultiRowQuery( wxString sql, bool readOnly );
	void FB_DBNextRow(void);
	virtual void FB_FetchRow(void) = 0;	// loads a row of data in this object's members
	// returns a new value from a generator
	long FB_GenNewValue( wxString generatorName );
	// returns true if the query did not return any rows
	bool FB_QueryReturnsNoRows( wxString sql );

public:
//	CBaseRec(void);
//	~CBaseRec(void);

	// insert this record into the database
	void DbInsert(void);

	// update this record into the database
	void DbUpdate(void);

	// delete this record from the database
	void DbDelete(void);

	// support for queries that return one or more rows
	bool IsEOF(void) {return eof;}				// returns true if we are beyond the leat row
	void DBStartMultiRowQuery( wxString sql, bool readOnly );	// starts the query and reads the first row, possibly setting EOF
	void DBNextRow(void);									// moves to the next row, possibly setting EOF


};


#endif