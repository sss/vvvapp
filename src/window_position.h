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

/*
a class that stores and resets the original position of a window

the position is stored using a config object
uses the wxWindow ID to identify each window

USAGE:

in the window's header file

	include the header:

		#include "window_position.h"

	add a private member:

		CWindowPosition m_WindowPosition;

in the cpp file

	at the end of Create() add:

		m_WindowPosition.SetWindow( this );
		m_WindowPosition.RestorePosition();

	in the destructor add:

		m_WindowPosition.SavePosition();


*/

#ifndef _WINDOW_POSITION_H_
#define _WINDOW_POSITION_H_

#include <wx/window.h>
#include "wx/config.h"

class CWindowPosition {

public:

	CWindowPosition( wxWindow *wp ) { window = wp; }
	CWindowPosition( void ) { window = NULL; }

	// sets the pointer to the managed window
	void SetWindow( wxWindow *wp )  { window = wp; }

	// saves the current position and size of the window
	void SavePosition( void );

	// restores size and position of the window
	void RestorePosition( void );

private:

	// a pointer to the window that will be managed by this instance
	wxWindow *window;

};

#endif



