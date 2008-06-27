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
// Name:        exportdata.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     13/04/2008 12:03:08
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _EXPORTDATA_H_
#define _EXPORTDATA_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "exportdata.h"
#endif

/*!
 * Includes
 */

////@begin includes
////@end includes
#include "window_position.h"

#include <wx/txtstrm.h>
#include <wx/file.h>
#include <wx/wfstream.h>

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CDIALOG_EXPORT_DATA 10014
#define ID_EXPORT_RADIOBOX_SEPARATOR 10025
#define ID_EXPORT_INCLUDE_HEADERS 10076
#define ID_EXPORT_RADIOBOX_EXPORT 10029
#define ID_EXPORT_FILENAME 10085
#define ID_EXPORT_BROWSE 10084
#define SYMBOL_CDIALOGEXPORTDATA_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CDIALOGEXPORTDATA_TITLE _("Export data")
#define SYMBOL_CDIALOGEXPORTDATA_IDNAME ID_CDIALOG_EXPORT_DATA
#define SYMBOL_CDIALOGEXPORTDATA_SIZE wxSize(400, 300)
#define SYMBOL_CDIALOGEXPORTDATA_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CDialogExportData class declaration
 */

class CDialogExportData: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CDialogExportData )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDialogExportData();
    CDialogExportData( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGEXPORTDATA_IDNAME, const wxString& caption = SYMBOL_CDIALOGEXPORTDATA_TITLE, const wxPoint& pos = SYMBOL_CDIALOGEXPORTDATA_POSITION, const wxSize& size = SYMBOL_CDIALOGEXPORTDATA_SIZE, long style = SYMBOL_CDIALOGEXPORTDATA_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGEXPORTDATA_IDNAME, const wxString& caption = SYMBOL_CDIALOGEXPORTDATA_TITLE, const wxPoint& pos = SYMBOL_CDIALOGEXPORTDATA_POSITION, const wxSize& size = SYMBOL_CDIALOGEXPORTDATA_SIZE, long style = SYMBOL_CDIALOGEXPORTDATA_STYLE );

    /// Destructor
    ~CDialogExportData();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CDialogExportData event handler declarations

    /// wxEVT_UPDATE_UI event handler for ID_EXPORT_RADIOBOX_EXPORT
    void OnExportRadioboxExportUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_EXPORT_BROWSE
    void OnExportBrowseClick( wxCommandEvent& event );

#if defined(__WXMSW__)
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

#endif
#if defined(__WXMSW__)
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

#endif
#if defined(__WXMAC__) || defined(__WXGTK__)
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

#endif
#if defined(__WXMAC__) || defined(__WXGTK__)
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

#endif
////@end CDialogExportData event handler declarations

////@begin CDialogExportData member function declarations

    long GetSelectedPhysicalFolderId() const { return m_SelectedPhysicalFolderId ; }
    void SetSelectedPhysicalFolderId(long value) { m_SelectedPhysicalFolderId = value ; }

    long GetSelectedVolumeId() const { return m_SelectedVolumeId ; }
    void SetSelectedVolumeId(long value) { m_SelectedVolumeId = value ; }

    long GetSelectedVirtualFolderId() const { return m_SelectedVirtualFolderId ; }
    void SetSelectedVirtualFolderId(long value) { m_SelectedVirtualFolderId = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogExportData member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogExportData member variables
    wxRadioBox* m_SeparatorRadioBox;
    wxCheckBox* m_IncludeHeadersCtrl;
    wxRadioBox* m_ExportRadioBox;
    wxTextCtrl* m_FileNameCtrl;
    wxButton* m_BrowseCtrl;
private:
    long m_SelectedPhysicalFolderId;
    long m_SelectedVolumeId;
    long m_SelectedVirtualFolderId;
////@end CDialogExportData member variables

private:

	CWindowPosition m_WindowPosition;

	// what shall we export?
	enum ExportScope {
		esAllPhysicalVolumes = 0,
		esSelectedPhysicalVolumeFolder,
		esSelectedVirtualFolder
	};

	// write the CSV headers line
	void WriteHeaders( wxTextOutputStream& fout, wxString separator );

	// export to a file the data about all physical volumes
	void ExportAllVolumes( wxTextOutputStream& fout, wxString separator );

	// export to a file the data about a selected volume
	void ExportSelectedVolume( wxTextOutputStream& fout, wxString separator, long volumeID );

	// export to a file the data about a selected physical folder and all its subfolders
	void ExportSelectedFolder( wxTextOutputStream& fout, wxString separator, long folderID, long volumeID );

	// export to a file the data about a selected virtual folder and all its subfolders
	void ExportSelectedVirtualFolder( wxTextOutputStream& fout, wxString separator, long virtualFolderID );

	// export to a file the data about a physical folder
	void ExportOnePhysicalFolder( wxTextOutputStream& fout, wxString separator, long folderID, long volumeID, wxString volumeName );

	// export to a file the data about a virtual folder
	void ExportOneVirtualFolder( wxTextOutputStream& fout, wxString separator, long virtualFolderID );

	// formats a string for correct CSV structure
	wxString FormatStringForCSV( wxString& s );

};

#endif
    // _EXPORTDATA_H_
