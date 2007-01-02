#ifndef __FIREBIRD_DB_H__
#define __FIREBIRD_DB_H__

#include <wx/string.h>

#include "../data_interface/base_db.h"
#include "../ibpp/core/ibpp.h"

using namespace std;

class CFirebirdDB :	public CBaseDB {
public:
	CFirebirdDB( wxString serverName, wxString databaseName, wxString userName, wxString password );
	~CFirebirdDB(void);

	wxString Connect(void);
	void Disconnect(void);

	IBPP::Database GetIBPPDB(void) {return db;};

	// creates and starts a transaction
	void TransactionStart( bool readOnly = false );
	// commit the transaction
	void TransactionCommit(void);
	// rolls back the transaction
	void TransactionRollback(void);
	// returns true if the transaction is started
	bool TransactionIsOpened(void);
	// returns a reference to the transaction
	IBPP::Transaction& TransactionGetReference(void) {return tr;}

protected:

	wxString serverName, databaseName, userName, password;
	IBPP::Database db;
	IBPP::Transaction tr;
};


#endif
