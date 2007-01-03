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