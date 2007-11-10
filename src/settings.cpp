/////////////////////////////////////////////////////////////////////////////
// Name:        settings.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     10/11/2007 09:58:37
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "settings.h"
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
#include "wx/bookctrl.h"
////@end includes

#include "settings.h"

////@begin XPM images
////@end XPM images


/*!
 * CDialogSettings type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CDialogSettings, wxPropertySheetDialog )


/*!
 * CDialogSettings event table definition
 */

BEGIN_EVENT_TABLE( CDialogSettings, wxPropertySheetDialog )

////@begin CDialogSettings event table entries
////@end CDialogSettings event table entries

END_EVENT_TABLE()


/*!
 * CDialogSettings constructors
 */

CDialogSettings::CDialogSettings()
{
    Init();
}

CDialogSettings::CDialogSettings( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CDialogSettings creator
 */

bool CDialogSettings::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CDialogSettings creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxPropertySheetDialog::Create( parent, id, caption, pos, size, style );

    SetSheetStyle(wxPROPSHEET_DEFAULT);
    CreateButtons(wxOK|wxCANCEL);
    CreateControls();
    LayoutDialog();
    Centre();
////@end CDialogSettings creation
    return true;
}


/*!
 * CDialogSettings destructor
 */

CDialogSettings::~CDialogSettings()
{
////@begin CDialogSettings destruction
////@end CDialogSettings destruction
}


/*!
 * Member initialisation
 */

void CDialogSettings::Init()
{
////@begin CDialogSettings member initialisation
////@end CDialogSettings member initialisation
}


/*!
 * Control creation for CDialogSettings
 */

void CDialogSettings::CreateControls()
{    
////@begin CDialogSettings content construction
    CDialogSettings* itemPropertySheetDialog1 = this;

    wxPanel* itemPanel2 = new wxPanel( GetBookCtrl(), ID_DS_GENERAL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer3);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer4, 0, wxGROW|wxALL, 5);
    wxCheckBox* itemCheckBox5 = new wxCheckBox( itemPanel2, ID_DS_REOPEN_CATALOG, _("Reopen the last used catalog at startup"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox5->SetValue(false);
    itemBoxSizer4->Add(itemCheckBox5, 0, wxALIGN_LEFT|wxALL, 5);

    GetBookCtrl()->AddPage(itemPanel2, _("General"));

    wxPanel* itemPanel6 = new wxPanel( GetBookCtrl(), ID_DS_MP3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
    itemPanel6->SetSizer(itemBoxSizer7);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer7->Add(itemBoxSizer8, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText9 = new wxStaticText( itemPanel6, wxID_STATIC, _("Show the following data for MP3 files:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer8->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxCheckBox* itemCheckBox11 = new wxCheckBox( itemPanel6, ID_CHECKBOX1, _("Artist"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox11->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox11, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox12 = new wxCheckBox( itemPanel6, ID_CHECKBOX2, _("Album"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox12->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox12, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox13 = new wxCheckBox( itemPanel6, ID_CHECKBOX3, _("Title"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox13->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox13, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox14 = new wxCheckBox( itemPanel6, ID_CHECKBOX4, _("Year"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox14->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox14, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox15 = new wxCheckBox( itemPanel6, ID_CHECKBOX5, _("Comment"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox15->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox15, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox16 = new wxCheckBox( itemPanel6, ID_CHECKBOX6, _("Track number"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox16->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox16, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox17 = new wxCheckBox( itemPanel6, ID_CHECKBOX7, _("Bitrate"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox17->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox17, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox18 = new wxCheckBox( itemPanel6, ID_CHECKBOX8, _("Sample rate"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox18->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox18, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox19 = new wxCheckBox( itemPanel6, ID_CHECKBOX9, _("Channels"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox19->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox19, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer8->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    GetBookCtrl()->AddPage(itemPanel6, _("MP3"));

////@end CDialogSettings content construction
}


/*!
 * Should we show tooltips?
 */

bool CDialogSettings::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDialogSettings::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CDialogSettings bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CDialogSettings bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDialogSettings::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CDialogSettings icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CDialogSettings icon retrieval
}
