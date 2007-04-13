/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2007, the VVV Development team

	Author: Fulvio Senore

    VVV is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VVV; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

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

	// derived to add exception handling
	virtual int OnRun();
	virtual bool OnExceptionInMainLoop();

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
