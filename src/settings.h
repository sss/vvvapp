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
#include "wx/valgen.h"
#include "wx/spinctrl.h"
////@end includes
#include "mainframe.h"
#include "window_position.h"

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxSpinCtrl;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG_SETTINGS 10048
#define ID_DS_GENERAL 10049
#define ID_DS_REOPEN_CATALOG 10051
#define ID_SPIN_BEEP_TIME 10020
#define ID_BTN_CHANGE_LANGUAGE 10092
#define ID_DS_MP3 10050
#define ID_DS_ARTIST 10052
#define ID_DS_ALBUM 10053
#define ID_DS_TITLE 10054
#define ID_DS_YEAR 10055
#define ID_DS_COMMENT 10056
#define ID_DS_TRACK_NUMBER 10057
#define ID_DS_GENRE 10061
#define ID_DS_LENGTH 10062
#define ID_DS_BITRATE 10058
#define ID_DS_SAMPLE_RATE 10059
#define ID_DS_CHANNELS 10060
#define ID_DS_SERVER 10063
#define ID_DS_CONNECT_SERVER 10064
#define ID_DS_SERVERNAME 10065
#define ID_DS_USERNAME 10066
#define ID_DS_PASSWORD 10067
#define ID_DS_TEST_CONNECTION 10068
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

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

////@begin CDialogSettings event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BTN_CHANGE_LANGUAGE
    void OnBtnChangeLanguageClick( wxCommandEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_DS_SERVERNAME
    void OnDsServernameUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_DS_USERNAME
    void OnDsUsernameUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_DS_PASSWORD
    void OnDsPasswordUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_DS_TEST_CONNECTION
    void OnDsTestConnectionClick( wxCommandEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_DS_TEST_CONNECTION
    void OnDsTestConnectionUpdate( wxUpdateUIEvent& event );

////@end CDialogSettings event handler declarations

////@begin CDialogSettings member function declarations

    bool* GetAmdColumnsToShow() const { return m_amdColumnsToShow ; }
    void SetAmdColumnsToShow(bool* value) { m_amdColumnsToShow = value ; }

    bool GetReopenCatalog() const { return m_ReopenCatalog ; }
    void SetReopenCatalog(bool value) { m_ReopenCatalog = value ; }

    bool GetConnectServer() const { return m_ConnectServer ; }
    void SetConnectServer(bool value) { m_ConnectServer = value ; }

    wxString GetServerName() const { return m_ServerName ; }
    void SetServerName(wxString value) { m_ServerName = value ; }

    wxString GetUsername() const { return m_Username ; }
    void SetUsername(wxString value) { m_Username = value ; }

    wxString GetPassword() const { return m_Password ; }
    void SetPassword(wxString value) { m_Password = value ; }

    int GetBeepTime() const { return m_BeepTime ; }
    void SetBeepTime(int value) { m_BeepTime = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CDialogSettings member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CDialogSettings member variables
    wxSpinCtrl* m_BeepTimeCtrl;
    wxCheckBox* m_chkArtist;
    wxCheckBox* m_chkAlbum;
    wxCheckBox* m_chkTitle;
    wxCheckBox* m_chkYear;
    wxCheckBox* m_chkComment;
    wxCheckBox* m_chkTrackNumber;
    wxCheckBox* m_chkGenre;
    wxCheckBox* m_chkLength;
    wxCheckBox* m_chkBitrate;
    wxCheckBox* m_chkSampleRate;
    wxCheckBox* m_chkChannels;
    wxCheckBox* m_ConnectServerCtrl;
    wxTextCtrl* m_ServerNameCtrl;
    wxTextCtrl* m_UsernameCtrl;
    wxTextCtrl* m_PasswordCtrl;
private:
    bool* m_amdColumnsToShow; // array of bools for visibility of audio metadata fields
    bool m_ReopenCatalog;
    bool m_ConnectServer;
    wxString m_ServerName;
    wxString m_Username;
    wxString m_Password;
    int m_BeepTime;
////@end CDialogSettings member variables

	bool TransferDataToWindow();
	bool TransferDataFromWindow();

	CWindowPosition m_WindowPosition;

};

#endif
    // _SETTINGS_H_
