/////////////////////////////////////////////////////////////////////////////
// Name:        object_description.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     03/08/2007 16:45:13
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "object_description.h"
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

#include "object_description.h"

////@begin XPM images
////@end XPM images


/*!
 * CDialogObjectDescription type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CDialogObjectDescription, wxDialog )


/*!
 * CDialogObjectDescription event table definition
 */

BEGIN_EVENT_TABLE( CDialogObjectDescription, wxDialog )

////@begin CDialogObjectDescription event table entries
////@end CDialogObjectDescription event table entries

END_EVENT_TABLE()


/*!
 * CDialogObjectDescription constructors
 */

CDialogObjectDescription::CDialogObjectDescription()
{
    Init();
}

CDialogObjectDescription::CDialogObjectDescription( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CDialogObjectDescription creator
 */

bool CDialogObjectDescription::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CDialogObjectDescription creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CDialogObjectDescription creation
    return true;
}


/*!
 * CDialogObjectDescription destructor
 */

CDialogObjectDescription::~CDialogObjectDescription()
{
////@begin CDialogObjectDescription destruction
////@end CDialogObjectDescription destruction
}


/*!
 * Member initialisation
 */

void CDialogObjectDescription::Init()
{
////@begin CDialogObjectDescription member initialisation
    m_ObjectNameStatic = NULL;
    m_TextControl = NULL;
////@end CDialogObjectDescription member initialisation
}


/*!
 * Control creation for CDialogObjectDescription
 */

void CDialogObjectDescription::CreateControls()
{    
////@begin CDialogObjectDescription content construction
    CDialogObjectDescription* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("Please enter the description for the following object:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText3, 0, wxALIGN_LEFT|wxALL, 5);

    m_ObjectNameStatic = new wxStaticText( itemDialog1, ID_STATIC_OBJECT_NAME, _("OBJECT NAME"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(m_ObjectNameStatic, 0, wxALIGN_LEFT|wxALL, 5);

    m_TextControl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE );
    itemBoxSizer2->Add(m_TextControl, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer6, 0, wxALIGN_RIGHT|wxALL, 5);

    wxButton* itemButton7 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton7->SetDefault();
    itemBoxSizer6->Add(itemButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton8 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButton8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end CDialogObjectDescription content construction
}


/*!
 * Should we show tooltips?
 */

bool CDialogObjectDescription::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDialogObjectDescription::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CDialogObjectDescription bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CDialogObjectDescription bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDialogObjectDescription::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CDialogObjectDescription icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CDialogObjectDescription icon retrieval
}


void CDialogObjectDescription::SetObjectName( const wxString& volName ) {
	m_ObjectNameStatic->SetLabel( volName );
}

void CDialogObjectDescription::SetDescription( const wxString& descr ) {
	m_TextControl->SetValue( descr );
}

wxString CDialogObjectDescription::GetDescription( void ) {
	return m_TextControl->GetValue();
}


