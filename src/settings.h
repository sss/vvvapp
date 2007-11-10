/////////////////////////////////////////////////////////////////////////////
// Name:        settings.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     10/11/2007 09:58:37
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "settings.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/propdlg.h"
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
#define ID_DIALOG_SETTINGS 10048
#define ID_DS_GENERAL 10049
#define ID_DS_REOPEN_CATALOG 10051
#define ID_DS_MP3 10050
#define ID_CHECKBOX1 10052
#define ID_CHECKBOX2 10053
#define ID_CHECKBOX3 10054
#define ID_CHECKBOX4 10055
#define ID_CHECKBOX5 10056
#define ID_CHECKBOX6 10057
#define ID_CHECKBOX7 10058
#define ID_CHECKBOX8 10059
#define ID_CHECKBOX9 10060
#define SYMBOL_CDIALOGSETTINGS_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_CDIALOGSETTINGS_TITLE _("Settings")
#define SYMBOL_CDIALOGSETTINGS_IDNAME ID_DIALOG_SETTINGS
#define SYMBOL_CDIALOGSETTINGS_SIZE wxSize(400, 300)
#define SYMBOL_CDIALOGSETTINGS_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CDialogSettings class declaration
 */

class CDialogSettings: public wxPropertySheetDialog
{    
    DECLARE_DYNAMIC_CLASS( CDialogSettings )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDialogSettings();
    CDialogSettings( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGSETTINGS_IDNAME, const wxString& caption = SYMBOL_CDIALOGSETTINGS_TITLE, const wxPoint& pos = SYMBOL_CDIALOGSETTINGS_POSITION, const wxSize& size = SYMBOL_CDIALOGSETTINGS_SIZE, long style = SYMBOL_CDIALOGSETTINGS_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGSETTINGS_IDNAME, const wxString& caption = SYMBOL_CDIALOGSETTINGS_TITLE, const wxPoint& pos = SYMBOL_CDIALOGSETTINGS_POSITION, const wxSize& size = SYMBOL_CDIALOGSETTINGS_SIZE, long style = SYMBOL_CDIALOGSETTINGS_STYLE );

    /// Destructor
    ~CDialogSettings();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CDialogSettings event handler declarations

////@end CDialogSettings event handler declarations

////@begin CDialogSettings member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogSettings member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogSettings member variables
////@end CDialogSettings member variables
};

#endif
    // _SETTINGS_H_
