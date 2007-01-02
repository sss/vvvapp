// Windows specific code
// compile only for the Windows version

#include <windows.h>
#include "windows_specific.h"

// return the name of a volume specified in a way like "C:\"
// return an empty string in case of error
wxString GetVolumeName( wxString volume ) {
	char vn[50];
	DWORD mcl, fsf;
	wxString retVal;

	if( GetVolumeInformation( volume.c_str(), vn, 49, NULL, &mcl, &fsf, NULL, 0 ) )
		retVal = vn;
	else
		retVal = "";
	
	return retVal;
}
