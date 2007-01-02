#ifndef __FILES_H__
#define __FILES_H__

#include <wx/string.h>
#include "wx/datetime.h"
#include "base_rec.h"

using namespace std;

class CFiles : public CBaseRec
{
public:
	CFiles(void);
	~CFiles(void);
	
	// data members ----------------------------
	wxString FileName;
	wxString FileExt;
	CNullableLong FileID;
	wxDateTime DateTime;
	wxLongLong FileSize;
	long PathID;
	bool IsFolder;

	// methods -----------------------------------

protected:

	// Firebird implementation of the database methods
	void FB_DbInsert(void);
	void FB_DbUpdate(void);
	void FB_DbDelete(void);
	void FB_FetchRow(void);

};


#endif
