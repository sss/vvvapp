/////////////////////////////////////////////////////////////////////////////
// Name:        object_description.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     03/08/2007 16:45:13
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _OBJECT_DESCRIPTION_H_
#define _OBJECT_DESCRIPTION_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "object_description.h"
#endif

/*!
 * Includes
 */

////@begin includes
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
#define ID_DIALOG_OBJECT_DESCRIPTION 10026
#define ID_STATIC_OBJECT_NAME 10027
#define ID_TEXTCTRL1 10028
#define SYMBOL_CDIALOGOBJECTDESCRIPTION_STYLE wxDEFAULT_DIALOG_STYLE|wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_CDIALOGOBJECTDESCRIPTION_TITLE _("Object Description")
#define SYMBOL_CDIALOGOBJECTDESCRIPTION_IDNAME ID_DIALOG_OBJECT_DESCRIPTION
#define SYMBOL_CDIALOGOBJECTDESCRIPTION_SIZE wxSize(400, 300)
#define SYMBOL_CDIALOGOBJECTDESCRIPTION_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CDialogObjectDescription class declaration
 */

class CDialogObjectDescription: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CDialogObjectDescription )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDialogObjectDescription();
    CDialogObjectDescription( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGOBJECTDESCRIPTION_IDNAME, const wxString& caption = SYMBOL_CDIALOGOBJECTDESCRIPTION_TITLE, const wxPoint& pos = SYMBOL_CDIALOGOBJECTDESCRIPTION_POSITION, const wxSize& size = SYMBOL_CDIALOGOBJECTDESCRIPTION_SIZE, long style = SYMBOL_CDIALOGOBJECTDESCRIPTION_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGOBJECTDESCRIPTION_IDNAME, const wxString& caption = SYMBOL_CDIALOGOBJECTDESCRIPTION_TITLE, const wxPoint& pos = SYMBOL_CDIALOGOBJECTDESCRIPTION_POSITION, const wxSize& size = SYMBOL_CDIALOGOBJECTDESCRIPTION_SIZE, long style = SYMBOL_CDIALOGOBJECTDESCRIPTION_STYLE );

    /// Destructor
    ~CDialogObjectDescription();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	// sets the volume name
	void SetObjectName( const wxString& volName );

	// sets the volume description
	void SetDescription( const wxString& descr );

	// gets the description
	wxString GetDescription( void );

////@begin CDialogObjectDescription event handler declarations

////@end CDialogObjectDescription event handler declarations

////@begin CDialogObjectDescription member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogObjectDescription member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogObjectDescription member variables
    wxStaticText* m_ObjectNameStatic;
    wxTextCtrl* m_TextControl;
////@end CDialogObjectDescription member variables
};

#endif
    // _OBJECT_DESCRIPTION_H_
