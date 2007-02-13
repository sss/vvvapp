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

	// returns the size of a file in human readable format (KB, MB and so on...)
	static wxString HumanReadableFileSize( wxLongLong size );

	// displays an error message
	static void MsgErr( wxString errMsg );

private:
	// name of the current application
	static wxString applicationName;
};



#endif
