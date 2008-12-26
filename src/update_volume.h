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
// Name:        update_volume.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     28/11/2008 10:39:59
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _UPDATE_VOLUME_H_
#define _UPDATE_VOLUME_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "update_volume.h"
#endif

/*!
 * Includes
 */

////@begin includes
////@end includes

#include "window_position.h"

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG_UPDATE_VOLUME 10087
#define ID_VOLUME_PATH 10023
#define ID_VOLUME_BROWSE 10019
#define ID_BUTTON_UPDATE 10088
#define ID_CURRENT_FOLDER 10024
#define SYMBOL_CDIALOGUPDATEVOLUME_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CDIALOGUPDATEVOLUME_TITLE _("Update Volume")
#define SYMBOL_CDIALOGUPDATEVOLUME_IDNAME ID_DIALOG_UPDATE_VOLUME
#define SYMBOL_CDIALOGUPDATEVOLUME_SIZE wxSize(400, 300)
#define SYMBOL_CDIALOGUPDATEVOLUME_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CDialogUpdateVolume class declaration
 */

class CDialogUpdateVolume: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CDialogUpdateVolume )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDialogUpdateVolume();
    CDialogUpdateVolume( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGUPDATEVOLUME_IDNAME, const wxString& caption = SYMBOL_CDIALOGUPDATEVOLUME_TITLE, const wxPoint& pos = SYMBOL_CDIALOGUPDATEVOLUME_POSITION, const wxSize& size = SYMBOL_CDIALOGUPDATEVOLUME_SIZE, long style = SYMBOL_CDIALOGUPDATEVOLUME_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGUPDATEVOLUME_IDNAME, const wxString& caption = SYMBOL_CDIALOGUPDATEVOLUME_TITLE, const wxPoint& pos = SYMBOL_CDIALOGUPDATEVOLUME_POSITION, const wxSize& size = SYMBOL_CDIALOGUPDATEVOLUME_SIZE, long style = SYMBOL_CDIALOGUPDATEVOLUME_STYLE );

    /// Destructor
    ~CDialogUpdateVolume();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CDialogUpdateVolume event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_VOLUME_BROWSE
    void OnVolumeBrowseClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_UPDATE
    void OnButtonUpdateClick( wxCommandEvent& event );

////@end CDialogUpdateVolume event handler declarations

////@begin CDialogUpdateVolume member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogUpdateVolume member function declarations

	// set volume data
	void SetVolumeData(wxString volumeName, long volumeID);
	
	/// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogUpdateVolume member variables
    wxStaticText* m_VolumeNameStatic;
    wxTextCtrl* m_VolumePath;
    wxButton* m_VolumeBrowse;
    wxButton* m_HelpButton;
    wxButton* m_UpdateButton;
    wxButton* m_CloseButton;
    wxStaticText* m_CurrentFolder;
////@end CDialogUpdateVolume member variables

private:

	// enable or disable all controls, used while cataloging to avoid recursion
	void EnableDisableControls( bool enabled );

	CWindowPosition m_WindowPosition;

	// volume to be updated
	long m_VolumeID;

};

#endif
    // _UPDATE_VOLUME_H_
