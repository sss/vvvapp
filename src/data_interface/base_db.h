#ifndef __BASE_DB_H__
#define __BASE_DB_H__

// defines a generic database object. What will be used is a derived class specific
// for each different database

// uses a Singleton pattern

#include <wx/string.h>
#include "../utils.h"

using namespace std;

class CBaseDB
{
public:

	// called to create a Firebird database. Add other functions to create other type of databases
	static void CreateFirebirdDatabase( wxString serverName, wxString databaseName, wxString userName, wxString password );
	
	// deletes the database object
	static void DeleteFirebirdDatabase(void);

	static CBaseDB* GetDatabase(void);

	// connects to the database
	virtual wxString Connect(void) = 0;
	// disconnects from the database
	virtual void Disconnect(void) = 0;

	// creates and starts a transaction
	virtual void TransactionStart( bool readOnly = false ) = 0;
	// commit the transaction
	virtual void TransactionCommit(void) = 0;
	// rolls back the transaction
	virtual void TransactionRollback(void) = 0;

protected:

//	CBaseDB();

private:

	static CBaseDB* _instance;
};


#endif