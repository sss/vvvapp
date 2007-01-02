#ifndef __UTILS_H__
#define __UTILS_H__

#include <wx/string.h>
#include <wx/msgdlg.h>
#include <string>

class wxMBConv;

class CUtils
{
public:

	// functions used to convert between std::string e wxString.
	// idea "borrowed" from the FlameRobin source code
	static std::string wx2std(const wxString& input, wxMBConv* conv = wxConvCurrent);
	static wxString std2wx(const std::string& input, wxMBConv* conv = wxConvCurrent);

	// displays an error message
	static void MsgErr( wxString errMsg );

private:
	// name of the current application
	static wxString applicationName;
};



#endif