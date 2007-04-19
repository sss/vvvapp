/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2007, the VVV Development team

	Author: Fulvio Senore

    VVV is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    VVV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VVV; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "utils.h"

wxString CUtils::applicationName = wxT("VVV");

std::string CUtils::wx2std(const wxString& input, wxMBConv* conv)
{
    if (input.empty())
        return "";
    if (!conv)
        conv = wxConvCurrent;
    return std::string(input.mb_str(*conv));
}
//-----------------------------------------------------------------------------
//! converts std:string to wxString
wxString CUtils::std2wx(const std::string& input, wxMBConv* conv)
{
    if (input.empty())
        return wxEmptyString;
    if (!conv)
        conv = wxConvCurrent;
    return wxString(input.c_str(), *conv);
}

void CUtils::MsgErr( wxString errMsg ){
	wxMessageDialog dialog( NULL, errMsg, applicationName, wxOK|wxICON_ERROR );
	dialog.ShowModal();
}

wxString CUtils::HumanReadableFileSize( wxLongLong size ) {
	wxString retVal;

	if( size > 1024*1024 ) {
		size = size / (1024*1024);
		retVal = size.ToString() + " MB";
	}
	else {
		if( size > 1024 ) {
			size = size / 1024;
			retVal = size.ToString() + " KB";
		}
		else {
			retVal = size.ToString();
		}
	}

	return retVal;
}
