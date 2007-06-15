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

/////////////////////////////////////////////////////////////////////////////
// Name:        vvv.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     29/12/2006 11:55:13
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "vvv.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if !wxUSE_EXCEPTIONS
    #error "This application requires wxUSE_EXCEPTIONS == 1"
#endif // !wxUSE_EXCEPTIONS

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "wx/log.h"
#include "wx/cmdline.h"
#include "wx/filename.h"

#include "vvv.h"
#include "data_interface/base_db.h"
#include "data_interface/data_error.h"

////@begin XPM images
////@end XPM images

/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( CVvvApp )
////@end implement app

/*!
 * CVvvApp type definition
 */

IMPLEMENT_CLASS( CVvvApp, wxApp )

/*!
 * CVvvApp event table definition
 */

BEGIN_EVENT_TABLE( CVvvApp, wxApp )

////@begin CVvvApp event table entries
////@end CVvvApp event table entries

END_EVENT_TABLE()


static const wxCmdLineEntryDesc g_cmdLineDesc[] = 
{
	{ wxCMD_LINE_PARAM, NULL, NULL, wxT("input catalog"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
	{ wxCMD_LINE_NONE }
};


/*!
 * Constructor for CVvvApp
 */

CVvvApp::CVvvApp()
{
    Init();
}

/*!
 * Member initialisation 
 */

void CVvvApp::Init()
{
////@begin CVvvApp member initialisation
////@end CVvvApp member initialisation
}
/*!
 * Initialisation for CVvvApp
 */

bool CVvvApp::OnInit()
{    

	// sets the config object
	SetVendorName(wxT("VVV"));
	SetAppName(wxT("VVV"));

    wxLocale m_locale;
    m_locale.Init();

	// parse the command line
	wxCmdLineParser cmdParser( g_cmdLineDesc, argc, argv );
	int res;
	{
		wxLogNull log;
		res = cmdParser.Parse( false );
	}
	if( res == -1 || res > 0 ) {
		m_CatalogName = "";
	}
	else {
		if( cmdParser.GetParamCount() > 0 ) {
			m_CatalogName = cmdParser.GetParam(0);
			wxFileName fName( m_CatalogName );
			fName.Normalize( wxPATH_NORM_LONG | wxPATH_NORM_DOTS | wxPATH_NORM_TILDE | wxPATH_NORM_ABSOLUTE );
			m_CatalogName = fName.GetFullPath();
		}
		else m_CatalogName = "";
	}

////@begin CVvvApp initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	CMainFrame* mainWindow = new CMainFrame( NULL, ID_MAIN_FRAME );
	mainWindow->Show(true);
////@end CVvvApp initialisation


	return true;
}

/*!
 * Cleanup for CVvvApp
 */
int CVvvApp::OnExit()
{    
	CBaseDB *db = CBaseDB::GetDatabase();
	if( db != NULL ) {
		CBaseDB::GetDatabase()->Disconnect();
		CBaseDB::DeleteFirebirdDatabase();
	}

////@begin CVvvApp cleanup
	return wxApp::OnExit();
////@end CVvvApp cleanup
}

// derived to add exception handling
int CVvvApp::OnRun() {

	try {
		return wxApp::OnRun();
	}
	catch( CDataErrorException& e ) {
		wxString s = _("An unexpected error has occurred. Here is a description of the error:\n\n");
		s += e.what();
		wxLogError( "%s", s.c_str() );
		return 3;
	}
	catch( IBPP::Exception& e ) {
		wxString s = _("An unexpected error has occurred. Here is a description of the error:\n\n");
		s += e.ErrorMessage();
		wxLogError( "%s", s.c_str() );
		return 3;
	}
	catch( ... ) {
		wxString s = _("An unexpected error has occurred. This application will be terminated");
		wxLogError( "%s", s.c_str() );
		return 3;
	}
}

// it does nothing to avoid an unuseful error message
bool CVvvApp::OnExceptionInMainLoop() {
//	return true;
	throw;
}
