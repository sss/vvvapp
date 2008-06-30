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
// Name:        exportdata.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     13/04/2008 12:03:08
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "exportdata.h"
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

#include "exportdata.h"
#include "utils.h"
#include "data_interface/files.h"
#include "data_interface/virtual_files.h"
#include "data_interface/paths.h"
#include "data_interface/virtual_paths.h"
#include "data_interface/volumes.h"
#include "vvv.h"

////@begin XPM images
////@end XPM images


/*!
 * CDialogExportData type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CDialogExportData, wxDialog )


/*!
 * CDialogExportData event table definition
 */

BEGIN_EVENT_TABLE( CDialogExportData, wxDialog )

////@begin CDialogExportData event table entries
    EVT_UPDATE_UI( ID_EXPORT_RADIOBOX_EXPORT, CDialogExportData::OnExportRadioboxExportUpdate )

    EVT_BUTTON( ID_EXPORT_BROWSE, CDialogExportData::OnExportBrowseClick )

#if defined(__WXMSW__)
    EVT_BUTTON( wxID_HELP, CDialogExportData::OnHelpClick )
#endif

#if defined(__WXMSW__)
    EVT_BUTTON( wxID_OK, CDialogExportData::OnOkClick )
#endif

#if defined(__WXMAC__) || defined(__WXGTK__)
    EVT_BUTTON( wxID_HELP, CDialogExportData::OnHelpClick )
#endif

#if defined(__WXMAC__) || defined(__WXGTK__)
    EVT_BUTTON( wxID_OK, CDialogExportData::OnOkClick )
#endif

////@end CDialogExportData event table entries

END_EVENT_TABLE()


/*!
 * CDialogExportData constructors
 */

CDialogExportData::CDialogExportData()
{
    Init();
}

CDialogExportData::CDialogExportData( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CDialogExportData creator
 */

bool CDialogExportData::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CDialogExportData creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CDialogExportData creation

	m_WindowPosition.SetWindow( this );
	m_WindowPosition.RestorePosition();

	return true;
}


/*!
 * CDialogExportData destructor
 */

CDialogExportData::~CDialogExportData()
{
////@begin CDialogExportData destruction
////@end CDialogExportData destruction

	m_WindowPosition.SavePosition();
}


/*!
 * Member initialisation
 */

void CDialogExportData::Init()
{
////@begin CDialogExportData member initialisation
    m_SelectedPhysicalFolderId = -1;
    m_SelectedVolumeId = -1;
    m_SelectedVirtualFolderId = -1;
    m_SeparatorRadioBox = NULL;
    m_IncludeHeadersCtrl = NULL;
    m_ExportRadioBox = NULL;
    m_FileNameCtrl = NULL;
    m_BrowseCtrl = NULL;
////@end CDialogExportData member initialisation
}


/*!
 * Control creation for CDialogExportData
 */

void CDialogExportData::CreateControls()
{    
////@begin CDialogExportData content construction
    CDialogExportData* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Use this window to export data to a CSV file"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALL, 5);

    wxArrayString m_SeparatorRadioBoxStrings;
    m_SeparatorRadioBoxStrings.Add(_("Comma"));
    m_SeparatorRadioBoxStrings.Add(_("TAB"));
    m_SeparatorRadioBoxStrings.Add(_("Pipe"));
    m_SeparatorRadioBox = new wxRadioBox( itemDialog1, ID_EXPORT_RADIOBOX_SEPARATOR, _("Separator"), wxDefaultPosition, wxDefaultSize, m_SeparatorRadioBoxStrings, 1, wxRA_SPECIFY_ROWS );
    m_SeparatorRadioBox->SetSelection(0);
    itemBoxSizer3->Add(m_SeparatorRadioBox, 0, wxALIGN_LEFT|wxALL, 5);

    m_IncludeHeadersCtrl = new wxCheckBox( itemDialog1, ID_EXPORT_INCLUDE_HEADERS, _("Include headers"), wxDefaultPosition, wxDefaultSize, 0 );
    m_IncludeHeadersCtrl->SetValue(true);
    itemBoxSizer3->Add(m_IncludeHeadersCtrl, 0, wxALIGN_LEFT|wxALL, 5);

    wxArrayString m_ExportRadioBoxStrings;
    m_ExportRadioBoxStrings.Add(_("All physical volumes"));
    m_ExportRadioBoxStrings.Add(_("Selected physical volume/folder"));
    m_ExportRadioBoxStrings.Add(_("Selected virtual folder"));
    m_ExportRadioBox = new wxRadioBox( itemDialog1, ID_EXPORT_RADIOBOX_EXPORT, _("Export"), wxDefaultPosition, wxDefaultSize, m_ExportRadioBoxStrings, 1, wxRA_SPECIFY_COLS );
    m_ExportRadioBox->SetSelection(0);
    itemBoxSizer3->Add(m_ExportRadioBox, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("File name:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer9, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    m_FileNameCtrl = new wxTextCtrl( itemDialog1, ID_EXPORT_FILENAME, _T(""), wxDefaultPosition, wxSize(250, -1), 0 );
    itemBoxSizer9->Add(m_FileNameCtrl, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BrowseCtrl = new wxButton( itemDialog1, ID_EXPORT_BROWSE, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer9->Add(m_BrowseCtrl, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

#if defined(__WXMSW__)
    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer12, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer12->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton15->SetDefault();
    itemBoxSizer12->Add(itemButton15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton16 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#endif

#if defined(__WXMAC__) || defined(__WXGTK__)
    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer17, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxButton* itemButton18 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer17->Add(itemButton18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer17->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton20 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer17->Add(itemButton20, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton21 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton21->SetDefault();
    itemBoxSizer17->Add(itemButton21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#endif

////@end CDialogExportData content construction
}


/*!
 * Should we show tooltips?
 */

bool CDialogExportData::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDialogExportData::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CDialogExportData bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CDialogExportData bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDialogExportData::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CDialogExportData icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CDialogExportData icon retrieval
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_EXPORT_BROWSE
 */

void CDialogExportData::OnExportBrowseClick( wxCommandEvent& WXUNUSED(event) )
{
	wxString caption = this->GetTitle();
	wxString wildcard = _("CSV files (*.csv;*.txt)|*.csv;*.txt|All files (*.*)|*.*");
	wxFileDialog fd( this, caption, wxEmptyString, wxEmptyString, wildcard, wxSAVE );
	if( fd.ShowModal() != wxID_OK ) return;
	wxString fileName = fd.GetPath();
	if ( fileName.empty() ) return;

	m_FileNameCtrl->SetValue( fileName );

}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
 */

void CDialogExportData::OnHelpClick( wxCommandEvent& WXUNUSED(event) )
{
	wxGetApp().GetHelpController()->DisplaySection( wxT("export_data.htm") );
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void CDialogExportData::OnOkClick( wxCommandEvent& WXUNUSED(event) )
{
	wxString fileName = m_FileNameCtrl->GetValue();
	if( fileName.empty() ) {
		CUtils::MsgErr( _("Please enter a file name") );
		return;
	}

	if( wxFileExists(fileName) ) {
		if( CUtils::MsgAskNo( _("The output file already exists: do you want to overwrite it?") ) ) {
			wxGetApp().Yield();	// refresh the screen
			if( !wxRemoveFile(fileName) ) {
				CUtils::MsgErr( _("Unable to create the file.") );
				return;
			}
		}
		else {
			return;
		}
	}

	// check if we can create the file
	wxFile f;
	{
		wxLogNull ln;
		if( !f.Create(fileName) ) {
			CUtils::MsgErr( _("Unable to create the file.") );
			return;
		}
	}
	f.Close();
	wxRemoveFile(fileName);

	wxBusyCursor wait;

	// open the output file
	wxFFileOutputStream output( fileName );
	wxTextOutputStream fout( output );

	wxString separator = wxT(",");
	if( m_SeparatorRadioBox->GetSelection() == 1 ) separator = wxT("\t");
	if( m_SeparatorRadioBox->GetSelection() == 2 ) separator = wxT("|");

	if( m_IncludeHeadersCtrl->GetValue() )
		WriteHeaders( fout, separator );

	ExportScope scope = (ExportScope) m_ExportRadioBox->GetSelection();
	switch( scope ) {
		case esSelectedPhysicalVolumeFolder:
			wxASSERT( m_SelectedVolumeId > 0 );
			if( m_SelectedPhysicalFolderId > 0 ) {
				wxASSERT( m_SelectedPhysicalFolderId > 0 );
				ExportSelectedFolder( fout, separator, m_SelectedPhysicalFolderId, m_SelectedVolumeId );
			}
			else {
				ExportSelectedVolume( fout, separator, m_SelectedVolumeId );
			}
			break;
		case esAllPhysicalVolumes:
			ExportAllVolumes( fout, separator );
			break;
		case esSelectedVirtualFolder:
			wxASSERT( m_SelectedVirtualFolderId > 0 );
			ExportSelectedVirtualFolder( fout, separator, m_SelectedVirtualFolderId );
			break;
	}


	EndModal( wxID_OK );
}


/*!
 * wxEVT_UPDATE_UI event handler for ID_EXPORT_RADIOBOX_EXPORT
 */

void CDialogExportData::OnExportRadioboxExportUpdate( wxUpdateUIEvent& WXUNUSED(event) )
{
	m_ExportRadioBox->Enable( esSelectedPhysicalVolumeFolder, m_SelectedVolumeId >= 0 || m_SelectedPhysicalFolderId >= 0 );
	m_ExportRadioBox->Enable( esSelectedVirtualFolder, m_SelectedVirtualFolderId >= 0 );
}


void CDialogExportData::ExportSelectedFolder( wxTextOutputStream& fout, wxString separator, long folderID, long volumeID ) {

	// retrieves the volume name
	CVolumes vol( volumeID );
	wxString volumeName = vol.VolumeName;
	ExportOnePhysicalFolder( fout, separator, folderID, volumeID, volumeName );

}


void CDialogExportData::ExportOnePhysicalFolder( wxTextOutputStream& fout, wxString separator, long folderID, long volumeID, wxString volumeName ) {
	wxString pathName;

	CPaths pth;
	pathName = CPaths::GetFullPath( folderID );
	// remove the volume name from the path
	pathName = pathName.Right( pathName.Len() - volumeName.Len() );

	CFiles files;
	files.DBStartQueryListFiles( folderID );
	while( !files.IsEOF() ) {

		if( !files.IsFolder() ) {
			fout << FormatStringForCSV(volumeName) << separator << FormatStringForCSV(pathName) << separator << FormatStringForCSV(files.FileName) << separator << files.FileSize << separator << FormatStringForCSV(files.FileExt) << separator << files.DateTime.FormatDate() + wxT(" ") + files.DateTime.FormatTime() << separator << FormatStringForCSV(files.FileDescription) << endl;
		}

		files.DBNextRow();
	}

	// look for subfolders
	pth.DBStartQueryListPaths( volumeID, folderID );
	while( !pth.IsEOF() ) {

		ExportOnePhysicalFolder( fout, separator, pth.PathID, volumeID, volumeName );

		pth.DBNextRow();
	}


}

void CDialogExportData::ExportSelectedVolume( wxTextOutputStream& fout, wxString separator, long volumeID ) {

	// retrieves the volume name
	CVolumes vol( volumeID );
	wxString volumeName = vol.VolumeName;

	CPaths pth;
	CNullableLong nl;
	nl.SetNull(true);
	pth.DBStartQueryListPaths( volumeID, nl );
	while( !pth.IsEOF() ) {
		long folderID = pth.PathID;
		ExportOnePhysicalFolder( fout, separator, folderID, volumeID, volumeName );
		pth.DBNextRow();
	}

}

void CDialogExportData::ExportAllVolumes( wxTextOutputStream& fout, wxString separator ) {

	CVolumes vol;
	vol.DBStartQueryListVolumes();
	while( !vol.IsEOF() ) {
		ExportSelectedVolume( fout, separator, vol.VolumeID );
		vol.DBNextRow();
	}

}

void CDialogExportData::ExportOneVirtualFolder( wxTextOutputStream& fout, wxString separator, long virtualFolderID ) {

	CVirtualFiles files;
	files.DBStartQueryListFiles( virtualFolderID );
	while( !files.IsEOF() ) {

		if( !files.IsFolder() ) {
			fout << FormatStringForCSV(files.FileName) << separator << files.FileSize << separator << FormatStringForCSV(files.FileExt) << separator << files.DateTime.FormatDate() + wxT(" ") + files.DateTime.FormatTime() << separator << FormatStringForCSV(files.FullPhysicalPath) << separator << FormatStringForCSV(files.FileDescription) << endl;
		}

		files.DBNextRow();
	}


	// look for subfolders
	CVirtualPaths pth;
	pth.DBStartQueryListPaths( virtualFolderID );
	while( !pth.IsEOF() ) {

		ExportOneVirtualFolder( fout, separator, pth.PathID );

		pth.DBNextRow();
	}
}

void CDialogExportData::ExportSelectedVirtualFolder( wxTextOutputStream& fout, wxString separator, long virtualFolderID ) {

	ExportOneVirtualFolder( fout, separator, virtualFolderID );
}

wxString CDialogExportData::FormatStringForCSV( wxString& s ) {
	s.Replace( wxT("\""), wxT("\"\"") );
	return wxT("\"") + s + wxT("\"");
}

void CDialogExportData::WriteHeaders( wxTextOutputStream& fout, wxString separator ) {

	ExportScope scope = (ExportScope) m_ExportRadioBox->GetSelection();
	if( scope == esSelectedVirtualFolder )
		fout << _("Name") << separator << _("Size") << separator << _("Ext") << separator << _("Last modified") << separator << _("PhysicalPath") << separator << _("Description") << endl;
	else
		fout << _("Volume") << separator << _("Path") << separator <<  _("Name") << separator << _("Size") << separator << _("Ext") << separator << _("Last modified") << separator << _("Description") << endl;
}


