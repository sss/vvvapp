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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "vvv.h"
#include "data_interface/base_db.h"

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
	// connects to the database
	CBaseDB::CreateFirebirdDatabase( "localhost", "CDCATALOG", "SYSDBA", "masterkey" );
	wxString stmp = CBaseDB::GetDatabase()->Connect();



	
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
	CBaseDB::GetDatabase()->Disconnect();
	CBaseDB::DeleteFirebirdDatabase();

////@begin CVvvApp cleanup
	return wxApp::OnExit();
////@end CVvvApp cleanup
}

