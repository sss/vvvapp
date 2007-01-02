// Windows specific code
// compile only for the Windows version

#include <wx/string.h>

// return the name of a volume specified in a way like "C:\"
// return an empty string in case of error
wxString GetVolumeName( wxString volume );

