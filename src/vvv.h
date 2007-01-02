/////////////////////////////////////////////////////////////////////////////
// Name:        vvv.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     29/12/2006 11:55:13
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _VVV_H_
#define _VVV_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "vvv.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "mainframe.h"
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
////@end control identifiers

/*!
 * CVvvApp class declaration
 */

class CVvvApp: public wxApp
{    
    DECLARE_CLASS( CVvvApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    CVvvApp();

    /// Initialises member variables
    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin CVvvApp event handler declarations

////@end CVvvApp event handler declarations

////@begin CVvvApp member function declarations

////@end CVvvApp member function declarations

////@begin CVvvApp member variables
////@end CVvvApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(CVvvApp)
////@end declare app

#endif
    // _VVV_H_
