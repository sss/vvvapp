/////////////////////////////////////////////////////////////////////////////
// Name:        volume_description.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     23/05/2007 18:28:52
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _VOLUME_DESCRIPTION_H_
#define _VOLUME_DESCRIPTION_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "volume_description.h"
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
#define ID_DIALOG_VOLUME_DESCRIPTION 10026
#define ID_STATIC_VOLUME_NAME 10027
#define ID_TEXTCTRL1 10028
#define SYMBOL_CDIALOGVOLUMEDESCRIPTION_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_CDIALOGVOLUMEDESCRIPTION_TITLE _("Volume description")
#define SYMBOL_CDIALOGVOLUMEDESCRIPTION_IDNAME ID_DIALOG_VOLUME_DESCRIPTION
#define SYMBOL_CDIALOGVOLUMEDESCRIPTION_SIZE wxSize(400, 300)
#define SYMBOL_CDIALOGVOLUMEDESCRIPTION_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * CDialogVolumeDescription class declaration
 */

class CDialogVolumeDescription: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CDialogVolumeDescription )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDialogVolumeDescription();
    CDialogVolumeDescription( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGVOLUMEDESCRIPTION_IDNAME, const wxString& caption = SYMBOL_CDIALOGVOLUMEDESCRIPTION_TITLE, const wxPoint& pos = SYMBOL_CDIALOGVOLUMEDESCRIPTION_POSITION, const wxSize& size = SYMBOL_CDIALOGVOLUMEDESCRIPTION_SIZE, long style = SYMBOL_CDIALOGVOLUMEDESCRIPTION_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGVOLUMEDESCRIPTION_IDNAME, const wxString& caption = SYMBOL_CDIALOGVOLUMEDESCRIPTION_TITLE, const wxPoint& pos = SYMBOL_CDIALOGVOLUMEDESCRIPTION_POSITION, const wxSize& size = SYMBOL_CDIALOGVOLUMEDESCRIPTION_SIZE, long style = SYMBOL_CDIALOGVOLUMEDESCRIPTION_STYLE );

    /// Destructor
    ~CDialogVolumeDescription();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	// sets the volume name
	void SetVolumeName( const wxString& volName );

	// sets the volume description
	void SetDescription( const wxString& descr );

	// gets the description
	wxString GetDescription( void );

////@begin CDialogVolumeDescription event handler declarations

////@end CDialogVolumeDescription event handler declarations

////@begin CDialogVolumeDescription member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogVolumeDescription member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogVolumeDescription member variables
    wxStaticText* m_VolumeNameStatic;
    wxTextCtrl* m_TextControl;
////@end CDialogVolumeDescription member variables
};

#endif
    // _VOLUME_DESCRIPTION_H_
