/////////////////////////////////////////////////////////////////////////////
// Name:        volume_description.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     23/05/2007 18:28:52
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "volume_description.h"
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

#include "volume_description.h"

////@begin XPM images
////@end XPM images

/*!
 * CDialogVolumeDescription type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CDialogVolumeDescription, wxDialog )

/*!
 * CDialogVolumeDescription event table definition
 */

BEGIN_EVENT_TABLE( CDialogVolumeDescription, wxDialog )

////@begin CDialogVolumeDescription event table entries
////@end CDialogVolumeDescription event table entries

END_EVENT_TABLE()

/*!
 * CDialogVolumeDescription constructors
 */

CDialogVolumeDescription::CDialogVolumeDescription()
{
    Init();
}

CDialogVolumeDescription::CDialogVolumeDescription( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

/*!
 * CDialogVolumeDescription creator
 */

bool CDialogVolumeDescription::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CDialogVolumeDescription creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CDialogVolumeDescription creation
    return true;
}

/*!
 * CDialogVolumeDescription destructor
 */

CDialogVolumeDescription::~CDialogVolumeDescription()
{
////@begin CDialogVolumeDescription destruction
////@end CDialogVolumeDescription destruction
}

/*!
 * Member initialisation 
 */

void CDialogVolumeDescription::Init()
{
////@begin CDialogVolumeDescription member initialisation
    m_VolumeNameStatic = NULL;
    m_TextControl = NULL;
////@end CDialogVolumeDescription member initialisation
}

/*!
 * Control creation for CDialogVolumeDescription
 */

void CDialogVolumeDescription::CreateControls()
{    
////@begin CDialogVolumeDescription content construction
    CDialogVolumeDescription* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("Please enter the description for the following volume:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText3, 0, wxALIGN_LEFT|wxALL, 5);

    m_VolumeNameStatic = new wxStaticText( itemDialog1, ID_STATIC_VOLUME_NAME, _("VOLUME_NAME"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(m_VolumeNameStatic, 0, wxALIGN_LEFT|wxALL, 5);

    m_TextControl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE );
    itemBoxSizer2->Add(m_TextControl, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton7 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton7->SetDefault();
    itemBoxSizer6->Add(itemButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton8 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButton8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end CDialogVolumeDescription content construction
}

/*!
 * Should we show tooltips?
 */

bool CDialogVolumeDescription::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDialogVolumeDescription::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CDialogVolumeDescription bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CDialogVolumeDescription bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDialogVolumeDescription::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CDialogVolumeDescription icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CDialogVolumeDescription icon retrieval
}

void CDialogVolumeDescription::SetVolumeName( const wxString& volName ) {
	m_VolumeNameStatic->SetLabel( volName );
}

void CDialogVolumeDescription::SetDescription( const wxString& descr ) {
	m_TextControl->SetValue( descr );
}

wxString CDialogVolumeDescription::GetDescription( void ) {
	return m_TextControl->GetValue();
}

