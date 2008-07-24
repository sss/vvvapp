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

#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "utils.h"

wxString CUtils::applicationName = wxT("VVV");
wxString CUtils::applicationVersion = wxT("0.8.5");
int CUtils::expectedDatabaseVersion = 14;
int CUtils::firstUnicodeDatabaseVersion = 14;
wxString CUtils::strucUpdateDbName = wxT("vvv-struct-update.fdb");

//-----------------------------------------------------------------------------
//! converts wxString to std::string
std::string CUtils::wx2std(const wxString& input, wxMBConv* conv)
{
    if (input.empty())
        return "";
    if (!conv)
        conv = wxConvCurrent;
    const wxWX2MBbuf buf(input.mb_str(*conv));
    // conversion may fail and return 0, which isn't a safe value to pass 
    // to std:string constructor
    if (!buf)
        return "";
    return std::string(buf);
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


// string conversion for database access
// the database uses UTF8 encoding
std::string CUtils::DBwx2std( const wxString& input ) {
	std::string s = wx2std( input, &wxConvUTF8 );
	return wx2std( input, &wxConvUTF8 );
}
wxString CUtils::DBstd2wx( const std::string& input ) {
	return std2wx( input, &wxConvUTF8 );
}



void CUtils::MsgErr( wxString errMsg ){
	wxMessageDialog dialog( NULL, errMsg, applicationName, wxOK|wxICON_ERROR );
	dialog.ShowModal();
}

void CUtils::MsgInfo( wxString infoMsg ){
	wxMessageDialog dialog( NULL, infoMsg, applicationName, wxOK|wxICON_INFORMATION );
	dialog.ShowModal();
}

bool CUtils::MsgAskNo( wxString msg ){
	wxMessageDialog dialog( NULL, msg, applicationName, wxYES_NO|wxNO_DEFAULT|wxICON_EXCLAMATION );
	return dialog.ShowModal() == wxID_YES;
}


wxString CUtils::HumanReadableFileSize( wxLongLong size ) {
	wxString retVal;

	if( size > 1024*1024 ) {
		size = size / (1024*1024);
		retVal = size.ToString() + wxT(" MB");
	}
	else {
		if( size > 1024 ) {
			size = size / 1024;
			retVal = size.ToString() + wxT(" KB");
		}
		else {
			retVal = size.ToString();
		}
	}

	return retVal;
}


wxString CUtils::GetApplicationName(void) {
	return applicationName;
}

wxString CUtils::GetApplicationVersion(void) {
	return applicationVersion;
}

int CUtils::GetExpectedDatabaseVersion(void) {
	return expectedDatabaseVersion;
}

int CUtils::GetFirstUnicodeDatabaseVersion(void) {
	return firstUnicodeDatabaseVersion;
}

wxString CUtils::GetStructUpdateDbName(void) {
	wxString appPath = wxStandardPaths::Get().GetExecutablePath();
	wxFileName fn( appPath );
	fn.SetFullName( strucUpdateDbName );
	wxString fullName = fn.GetFullPath();
	return fullName;
}


// converts a long to a string
wxString CUtils::long2string( long val ) {
	wxString retVal;
	retVal.Printf( wxT("%d"), val );
	return retVal;
}



wxString CUtils::Encrypt( wxString s ) {
	wxString key = wxT("w2m5t7i0g4ndnra5s4lfdpvlyrepfjemwksdjfrpwuanrtogbjentruglk60947235128");
	wxString sout( wxT(" "), s.Len() );
	size_t k;

	for( k = 0; k < s.Len(); k++ ) {
		char ch = s[k] ^ key[k % key.Len()];
		sout[k] = ch;
	}

	return sout;
}

wxString CUtils::GetHelpFileName(void) {
	wxString appPath = wxStandardPaths::Get().GetExecutablePath();
	wxFileName fn( appPath );
	fn.SetFullName( wxT("vvv") );
	wxString fullName = fn.GetFullPath();
	return fullName;
}


