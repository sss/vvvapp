/////////////////////////////////////////////////////////////////////////////
// Name:        restore.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     26/06/2008 18:12:28
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _RESTORE_H_
#define _RESTORE_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "restore.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/valgen.h"
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
#define ID_DIALOG_RESTORE 10079
#define ID_RESTOREDIALOG_BACKUP 10081
#define ID_RESTOREDIALOG_BROWSE_BACKUP 10082
#define ID_RESTOREDIALOG_CATALOG 10080
#define ID_RESTOREDIALOG_BROWSE_CATALOG 10083
#define SYMBOL_CDIALOGRESTORE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CDIALOGRESTORE_TITLE _("Restore")
#define SYMBOL_CDIALOGRESTORE_IDNAME ID_DIALOG_RESTORE
#define SYMBOL_CDIALOGRESTORE_SIZE wxSize(400, 300)
#define SYMBOL_CDIALOGRESTORE_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CDialogRestore class declaration
 */

class CDialogRestore: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CDialogRestore )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDialogRestore();
    CDialogRestore( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGRESTORE_IDNAME, const wxString& caption = SYMBOL_CDIALOGRESTORE_TITLE, const wxPoint& pos = SYMBOL_CDIALOGRESTORE_POSITION, const wxSize& size = SYMBOL_CDIALOGRESTORE_SIZE, long style = SYMBOL_CDIALOGRESTORE_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDIALOGRESTORE_IDNAME, const wxString& caption = SYMBOL_CDIALOGRESTORE_TITLE, const wxPoint& pos = SYMBOL_CDIALOGRESTORE_POSITION, const wxSize& size = SYMBOL_CDIALOGRESTORE_SIZE, long style = SYMBOL_CDIALOGRESTORE_STYLE );

    /// Destructor
    ~CDialogRestore();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CDialogRestore event handler declarations

    /// wxEVT_INIT_DIALOG event handler for ID_DIALOG_RESTORE
    void OnInitDialog( wxInitDialogEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RESTOREDIALOG_BROWSE_BACKUP
    void OnRestoredialogBrowseBackupClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RESTOREDIALOG_BROWSE_CATALOG
    void OnRestoredialogBrowseCatalogClick( wxCommandEvent& event );

#if defined(__WXMSW__)
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

#endif
#if defined(__WXMAC__) || defined(__WXGTK__)
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

#endif
////@end CDialogRestore event handler declarations

////@begin CDialogRestore member function declarations

    wxString GetCatalogName() const { return m_CatalogName ; }
    void SetCatalogName(wxString value) { m_CatalogName = value ; }

    wxString GetBackupName() const { return m_BackupName ; }
    void SetBackupName(wxString value) { m_BackupName = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogRestore member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogRestore member variables
    wxTextCtrl* m_BackupNameCtrl;
    wxButton* m_BrowseBackupCtrl;
    wxTextCtrl* m_CatalogNameCtrl;
    wxButton* m_BrowseCatalogCtrl;
private:
    wxString m_CatalogName;
    wxString m_BackupName;
////@end CDialogRestore member variables

	CWindowPosition m_WindowPosition;

};

#endif
    // _RESTORE_H_
