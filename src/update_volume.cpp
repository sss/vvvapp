/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2007-2008, the VVV Development team

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
// Name:        update_volume.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     28/11/2008 10:39:59
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "update_volume.h"
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

#include "update_volume.h"
#include "utils.h"
#include "long_task_beep.h"
#include "catalog_volume_functions.h"

////@begin XPM images
////@end XPM images


/*!
 * CDialogUpdateVolume type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CDialogUpdateVolume, wxDialog )


/*!
 * CDialogUpdateVolume event table definition
 */

BEGIN_EVENT_TABLE( CDialogUpdateVolume, wxDialog )

////@begin CDialogUpdateVolume event table entries
    EVT_BUTTON( ID_VOLUME_BROWSE, CDialogUpdateVolume::OnVolumeBrowseClick )

    EVT_BUTTON( ID_BUTTON_UPDATE, CDialogUpdateVolume::OnButtonUpdateClick )

////@end CDialogUpdateVolume event table entries

END_EVENT_TABLE()


/*!
 * CDialogUpdateVolume constructors
 */

CDialogUpdateVolume::CDialogUpdateVolume()
{
    Init();
}

CDialogUpdateVolume::CDialogUpdateVolume( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CDialogUpdateVolume creator
 */

bool CDialogUpdateVolume::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CDialogUpdateVolume creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CDialogUpdateVolume creation

	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->SetPath(wxT("/CatalogVolume"));
	wxString catalogPath = pConfig->Read( wxT("CatalogPath"), wxT("") );
	m_VolumePath->SetValue( catalogPath );

	m_WindowPosition.SetWindow( this );
	m_WindowPosition.RestorePosition();

    return true;
}


/*!
 * CDialogUpdateVolume destructor
 */

CDialogUpdateVolume::~CDialogUpdateVolume()
{
////@begin CDialogUpdateVolume destruction
////@end CDialogUpdateVolume destruction

	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->SetPath(wxT("/CatalogVolume"));
	wxString catalogPath = m_VolumePath->GetValue();
	pConfig->Write( wxT("CatalogPath"), catalogPath );

	m_WindowPosition.SavePosition();
}


/*!
 * Member initialisation
 */

void CDialogUpdateVolume::Init()
{
////@begin CDialogUpdateVolume member initialisation
    m_VolumeNameStatic = NULL;
    m_VolumePath = NULL;
    m_VolumeBrowse = NULL;
    m_HelpButton = NULL;
    m_UpdateButton = NULL;
    m_CloseButton = NULL;
    m_CurrentFolder = NULL;
////@end CDialogUpdateVolume member initialisation
}


/*!
 * Control creation for CDialogUpdateVolume
 */

void CDialogUpdateVolume::CreateControls()
{    
////@begin CDialogUpdateVolume content construction
    CDialogUpdateVolume* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("You are about to update the following volume:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText3, 0, wxALIGN_LEFT|wxALL, 5);

    m_VolumeNameStatic = new wxStaticText( itemDialog1, wxID_STATIC, _("VOLUME NAME"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(m_VolumeNameStatic, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer2->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Enter or select the path to volume to update"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer7, 0, wxGROW|wxBOTTOM, 5);

    m_VolumePath = new wxTextCtrl( itemDialog1, ID_VOLUME_PATH, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add(m_VolumePath, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_VolumeBrowse = new wxButton( itemDialog1, ID_VOLUME_BROWSE, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer7->Add(m_VolumeBrowse, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer10, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    m_HelpButton = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(m_HelpButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer10->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_UpdateButton = new wxButton( itemDialog1, ID_BUTTON_UPDATE, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(m_UpdateButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CloseButton = new wxButton( itemDialog1, wxID_CANCEL, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(m_CloseButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CurrentFolder = new wxStaticText( itemDialog1, ID_CURRENT_FOLDER, _("Current folder"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(m_CurrentFolder, 0, wxGROW|wxALL, 5);

////@end CDialogUpdateVolume content construction

	m_CurrentFolder->SetLabel( wxEmptyString );
}


/*!
 * Should we show tooltips?
 */

bool CDialogUpdateVolume::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDialogUpdateVolume::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CDialogUpdateVolume bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CDialogUpdateVolume bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDialogUpdateVolume::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CDialogUpdateVolume icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CDialogUpdateVolume icon retrieval
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_CATALOG
 */

void CDialogUpdateVolume::OnButtonUpdateClick( wxCommandEvent& WXUNUSED(event) )
{
	wxString path = m_VolumePath->GetValue();
	if( path == wxEmptyString ) {
		CUtils::MsgErr( _("The volume path is missing") );
		return;
	}

	wxBusyCursor bc;
	CLongTaskBeep ltb;

	EnableDisableControls( false );

	// creates an object that will be used to catalog data
	CCatalogVolumeFunctions cvf( m_CurrentFolder );
	cvf.UpdateVolume( path, m_VolumeID );

	EnableDisableControls( true );

	m_CurrentFolder->SetLabel( wxEmptyString );

	EndModal( wxID_OK );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_VOLUME_BROWSE
 */

void CDialogUpdateVolume::OnVolumeBrowseClick( wxCommandEvent& WXUNUSED(event) )
{
	wxDirDialog dlg( this, _("Select the volume to catalog"), wxEmptyString, wxDD_DEFAULT_STYLE|wxDD_DIR_MUST_EXIST );
	if( dlg.ShowModal() == wxID_OK )
		m_VolumePath->SetValue( dlg.GetPath() );
}

void CDialogUpdateVolume::EnableDisableControls( bool enabled ) {

	m_VolumeBrowse->Enable( enabled );
	m_HelpButton->Enable( enabled );
	m_UpdateButton->Enable( enabled );
	m_CloseButton->Enable( enabled );
}

void CDialogUpdateVolume::SetVolumeData(wxString volumeName, long volumeID) {
	m_VolumeID = volumeID;
	m_VolumeNameStatic->SetLabel( volumeName );
}



