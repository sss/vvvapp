#ifndef __PATHS_H__
#define __PATHS_H__

#include <wx/string.h>

#include "base_rec.h"

using namespace std;

class CPaths : public CBaseRec
{
public:
	CPaths(void);
	~CPaths(void);
	
	// data members ----------------------------
	wxString PathName;
	CNullableLong PathID;
	CNullableLong VolumeID;
	CNullableLong FatherID;

	// methods -----------------------------------

protected:

	// Firebird implementation of the database methods
	void FB_DbInsert(void);
	void FB_DbUpdate(void);
	void FB_DbDelete(void);
	void FB_FetchRow(void);

};


#endif
