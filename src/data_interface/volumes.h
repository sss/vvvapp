#ifndef __VOLUMES_H__
#define __VOLUMES_H__

#include <wx/string.h>

#include "base_rec.h"

using namespace std;

class CVolumes : public CBaseRec
{
public:
	CVolumes(void);
	~CVolumes(void);

	// returns true if this->VolumeName is already present in the database
	bool NameExists(void);
	
	// data members ----------------------------
	wxString VolumeName;
	CNullableLong VolumeID;

	// methods -----------------------------------

protected:

	// Firebird implementation of the database methods
	void FB_DbInsert(void);
	void FB_DbUpdate(void);
	void FB_DbDelete(void);
	void FB_FetchRow(void);
	bool FB_NameExists(void);

};


#endif