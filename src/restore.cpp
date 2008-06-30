/////////////////////////////////////////////////////////////////////////////
// Name:        restore.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     26/06/2008 18:12:28
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "restore.h"
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

#include "restore.h"
#include "vvv.h"

////@begin XPM images
////@end XPM images


/*!
 * CDialogRestore type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CDialogRestore, wxDialog )


/*!
 * CDialogRestore event table definition
 */

BEGIN_EVENT_TABLE( CDialogRestore, wxDialog )

////@begin CDialogRestore event table entries
    EVT_INIT_DIALOG( CDialogRestore::OnInitDialog )

    EVT_BUTTON( ID_RESTOREDIALOG_BROWSE_BACKUP, CDialogRestore::OnRestoredialogBrowseBackupClick )

    EVT_BUTTON( ID_RESTOREDIALOG_BROWSE_CATALOG, CDialogRestore::OnRestoredialogBrowseCatalogClick )

#if defined(__WXMSW__)
    EVT_BUTTON( wxID_HELP, CDialogRestore::OnHelpClick )
#endif

#if defined(__WXMAC__) || defined(__WXGTK__)
    EVT_BUTTON( wxID_HELP, CDialogRestore::OnHelpClick )
#endif

////@end CDialogRestore event table entries

END_EVENT_TABLE()


/*!
 * CDialogRestore constructors
 */

CDialogRestore::CDialogRestore()
{
    Init();
}

CDialogRestore::CDialogRestore( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CDialogRestore creator
 */

bool CDialogRestore::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CDialogRestore creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CDialogRestore creation

	m_WindowPosition.SetWindow( this );
	m_WindowPosition.RestorePosition();

    return true;
}


/*!
 * CDialogRestore destructor
 */

CDialogRestore::~CDialogRestore()
{
////@begin CDialogRestore destruction
////@end CDialogRestore destruction

	m_WindowPosition.SavePosition();
}


/*!
 * Member initialisation
 */

void CDialogRestore::Init()
{
////@begin CDialogRestore member initialisation
    m_BackupNameCtrl = NULL;
    m_BrowseBackupCtrl = NULL;
    m_CatalogNameCtrl = NULL;
    m_BrowseCatalogCtrl = NULL;
////@end CDialogRestore member initialisation
}


/*!
 * Control creation for CDialogRestore
 */

void CDialogRestore::CreateControls()
{    
////@begin CDialogRestore content construction
    CDialogRestore* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("You are about to create a new catalog from a backup file.\n\nEnter the complete path to the backup file and to the catalog file that will be created.\nYou cannot enter the name of an existing catalog."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer3->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Backup file:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer7, 0, wxGROW|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_BackupNameCtrl = new wxTextCtrl( itemDialog1, ID_RESTOREDIALOG_BACKUP, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add(m_BackupNameCtrl, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BrowseBackupCtrl = new wxButton( itemDialog1, ID_RESTOREDIALOG_BROWSE_BACKUP, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer7->Add(m_BrowseBackupCtrl, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemDialog1, wxID_STATIC, _("New catalog:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer11, 0, wxGROW|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_CatalogNameCtrl = new wxTextCtrl( itemDialog1, ID_RESTOREDIALOG_CATALOG, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(m_CatalogNameCtrl, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BrowseCatalogCtrl = new wxButton( itemDialog1, ID_RESTOREDIALOG_BROWSE_CATALOG, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer11->Add(m_BrowseCatalogCtrl, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

#if defined(__WXMSW__)
    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer14, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add(itemButton15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer14->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton17 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton17->SetDefault();
    itemBoxSizer14->Add(itemButton17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton18 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add(itemButton18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#endif

#if defined(__WXMAC__) || defined(__WXGTK__)
    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer19, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxButton* itemButton20 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer19->Add(itemButton20, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer19->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton22 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer19->Add(itemButton22, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton23 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton23->SetDefault();
    itemBoxSizer19->Add(itemButton23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#endif

    // Set validators
    m_BackupNameCtrl->SetValidator( wxGenericValidator(& m_BackupName) );
    m_CatalogNameCtrl->SetValidator( wxGenericValidator(& m_CatalogName) );
////@end CDialogRestore content construction
}


/*!
 * wxEVT_INIT_DIALOG event handler for ID_DIALOG_RESTORE
 */

void CDialogRestore::OnInitDialog( wxInitDialogEvent& event )
{
////@begin wxEVT_INIT_DIALOG event handler for ID_DIALOG_RESTORE in CDialogRestore.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_INIT_DIALOG event handler for ID_DIALOG_RESTORE in CDialogRestore. 
}




/*!
 * Should we show tooltips?
 */

bool CDialogRestore::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDialogRestore::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CDialogRestore bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CDialogRestore bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDialogRestore::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CDialogRestore icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CDialogRestore icon retrieval
}




/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RESTOREDIALOG_BROWSE_BACKUP
 */

void CDialogRestore::OnRestoredialogBrowseBackupClick( wxCommandEvent& WXUNUSED(event) )
{
	wxString wildcard;
	wxString caption = _("Select backup file");
	wildcard = _("VVV backup files (*.vvvbk)|*.vvvbk|All files (*.*)|*.*");
	wxFileDialog fd( this, caption, wxEmptyString, wxEmptyString, wildcard, wxOPEN );
	if( fd.ShowModal() != wxID_OK ) return;
	wxString backupFile = fd.GetPath();
	if ( backupFile.empty() ) return;

	m_BackupNameCtrl->SetValue( backupFile );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RESTOREDIALOG_BROWSE_CATALOG
 */

void CDialogRestore::OnRestoredialogBrowseCatalogClick( wxCommandEvent& WXUNUSED(event) )
{
	wxString wildcard;
	wxString caption = _("Catalog file");
	wildcard = _("VVV files (*.vvv)|*.vvv|All files (*.*)|*.*");
	wxFileDialog fd( this, caption, wxEmptyString, wxEmptyString, wildcard, wxSAVE );
	if( fd.ShowModal() != wxID_OK ) return;
	wxString databaseFile = fd.GetPath();
	if ( databaseFile.empty() ) return;

	m_CatalogNameCtrl->SetValue( databaseFile );
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
 */

void CDialogRestore::OnHelpClick( wxCommandEvent& WXUNUSED(event) )
{
	wxGetApp().GetHelpController()->DisplaySection( wxT("restore_catalog.htm") );
}
