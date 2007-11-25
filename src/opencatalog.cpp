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
// Name:        opencatalog.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     24/11/2007 19:25:02
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "opencatalog.h"
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

#include "opencatalog.h"

////@begin XPM images
////@end XPM images


/*!
 * CDialogOpenCatalog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CDialogOpenCatalog, wxDialog )


/*!
 * CDialogOpenCatalog event table definition
 */

BEGIN_EVENT_TABLE( CDialogOpenCatalog, wxDialog )

////@begin CDialogOpenCatalog event table entries
    EVT_INIT_DIALOG( CDialogOpenCatalog::OnInitDialog )

    EVT_BUTTON( ID_OPENDIALOG_BROWSE, CDialogOpenCatalog::OnOpendialogBrowseClick )

////@end CDialogOpenCatalog event table entries

END_EVENT_TABLE()


/*!
 * CDialogOpenCatalog constructors
 */

CDialogOpenCatalog::CDialogOpenCatalog()
{
    Init();
}

CDialogOpenCatalog::CDialogOpenCatalog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CDialogOpenCatalog creator
 */

bool CDialogOpenCatalog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CDialogOpenCatalog creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CDialogOpenCatalog creation
    return true;
}


/*!
 * CDialogOpenCatalog destructor
 */

CDialogOpenCatalog::~CDialogOpenCatalog()
{
////@begin CDialogOpenCatalog destruction
////@end CDialogOpenCatalog destruction
}


/*!
 * Member initialisation
 */

void CDialogOpenCatalog::Init()
{
////@begin CDialogOpenCatalog member initialisation
    m_CatalogNameCtrl = NULL;
    m_BrowseCtrl = NULL;
////@end CDialogOpenCatalog member initialisation
}


/*!
 * Control creation for CDialogOpenCatalog
 */

void CDialogOpenCatalog::CreateControls()
{    
////@begin CDialogOpenCatalog content construction
    CDialogOpenCatalog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("You are about to open a catalog located on the server.\n\nEnter the alias or the complete path to the catalog file.\nRemember that the path must be relative to the server, not to the client."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer3->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer6, 0, wxGROW|wxALL, 5);

    m_CatalogNameCtrl = new wxTextCtrl( itemDialog1, ID_OPENDIALOG_CATALOG_NAME, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(m_CatalogNameCtrl, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BrowseCtrl = new wxButton( itemDialog1, ID_OPENDIALOG_BROWSE, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer6->Add(m_BrowseCtrl, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer9, 0, wxALIGN_RIGHT|wxALL, 5);

    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton10->SetDefault();
    itemBoxSizer9->Add(itemButton10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add(itemButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Set validators
    m_CatalogNameCtrl->SetValidator( wxGenericValidator(& m_CatalogName) );
////@end CDialogOpenCatalog content construction

}


/*!
 * Should we show tooltips?
 */

bool CDialogOpenCatalog::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDialogOpenCatalog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CDialogOpenCatalog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CDialogOpenCatalog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDialogOpenCatalog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CDialogOpenCatalog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CDialogOpenCatalog icon retrieval
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_OPENDIALOG_BROWSE
 */

void CDialogOpenCatalog::OnOpendialogBrowseClick( wxCommandEvent& WXUNUSED(event) )
{
	wxString caption = this->GetTitle();
	wxString wildcard = _("VVV  files (*.vvv)|*.vvv|All files (*.*)|*.*");
	wxFileDialog fd( this, caption, wxEmptyString, wxEmptyString, wildcard, m_Action == "O" ? wxOPEN : wxSAVE );
	if( fd.ShowModal() != wxID_OK ) return;
	wxString databaseFile = fd.GetPath();
	if ( databaseFile.empty() ) return;

	m_CatalogNameCtrl->SetValue( databaseFile );
}


/*!
 * wxEVT_INIT_DIALOG event handler for ID_CDIALOG_OPEN_CATALOG
 */

void CDialogOpenCatalog::OnInitDialog( wxInitDialogEvent& event )
{
	wxASSERT( m_Action == "O" || m_Action == "N" );

	if( m_Action == "O" ) 
		// called as an open dialog
		SetTitle( _("Open Catalog") );
	else 
		// called as a NEW dialog
		SetTitle( _("New Catalog") );
	if( !m_ShowBrowseButton )
		m_BrowseCtrl->Show( false );

	wxDialog::OnInitDialog( event );

}

