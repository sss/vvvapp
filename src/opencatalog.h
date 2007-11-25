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
// Name:        opencatalog.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     24/11/2007 19:25:02
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _OPENCATALOG_H_
#define _OPENCATALOG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "opencatalog.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/valgen.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CDIALOG_OPEN_CATALOG 10069
#define ID_OPENDIALOG_CATALOG_NAME 10070
#define ID_OPENDIALOG_BROWSE 10071
#define SYMBOL_CDIALOGOPENCATALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CDIALOGOPENCATALOG_TITLE _("Open Catalog")
#define SYMBOL_CDIALOGOPENCATALOG_IDNAME ID_CDIALOG_OPEN_CATALOG
#define SYMBOL_CDIALOGOPENCATALOG_SIZE wxSize(400, 300)
#define SYMBOL_CDIALOGOPENCATALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CDialogOpenCatalog class declaration
 */

class CDialogOpenCatalog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CDialogOpenCatalog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDialogOpenCatalog();
    CDialogOpenCatalog( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGOPENCATALOG_IDNAME, const wxString& caption = SYMBOL_CDIALOGOPENCATALOG_TITLE, const wxPoint& pos = SYMBOL_CDIALOGOPENCATALOG_POSITION, const wxSize& size = SYMBOL_CDIALOGOPENCATALOG_SIZE, long style = SYMBOL_CDIALOGOPENCATALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGOPENCATALOG_IDNAME, const wxString& caption = SYMBOL_CDIALOGOPENCATALOG_TITLE, const wxPoint& pos = SYMBOL_CDIALOGOPENCATALOG_POSITION, const wxSize& size = SYMBOL_CDIALOGOPENCATALOG_SIZE, long style = SYMBOL_CDIALOGOPENCATALOG_STYLE );

    /// Destructor
    ~CDialogOpenCatalog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CDialogOpenCatalog event handler declarations

    /// wxEVT_INIT_DIALOG event handler for ID_CDIALOG_OPEN_CATALOG
    void OnInitDialog( wxInitDialogEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_OPENDIALOG_BROWSE
    void OnOpendialogBrowseClick( wxCommandEvent& event );

////@end CDialogOpenCatalog event handler declarations

////@begin CDialogOpenCatalog member function declarations

    wxString GetCatalogName() const { return m_CatalogName ; }
    void SetCatalogName(wxString value) { m_CatalogName = value ; }

    wxString GetAction() const { return m_Action ; }
    void SetAction(wxString value) { m_Action = value ; }

    bool GetShowBrowseButton() const { return m_ShowBrowseButton ; }
    void SetShowBrowseButton(bool value) { m_ShowBrowseButton = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogOpenCatalog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogOpenCatalog member variables
    wxTextCtrl* m_CatalogNameCtrl;
    wxButton* m_BrowseCtrl;
private:
    wxString m_CatalogName;
    wxString m_Action; // "O" for OPEN, "N" for NEW
    bool m_ShowBrowseButton; // if true the dialog will show a "Browse" button near the catalog name
////@end CDialogOpenCatalog member variables
};

#endif
    // _OPENCATALOG_H_
