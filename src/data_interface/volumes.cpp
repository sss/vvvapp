#include "volumes.h"

CVolumes::CVolumes(void) {
	VolumeName = "";
}

CVolumes::~CVolumes(void) {
}


bool CVolumes::NameExists(void) {
	bool retVal = true;

	switch( DatabaseType ) {
		case dbtFirebird:
			retVal = FB_NameExists();
			break;
	}

	return retVal;
}

