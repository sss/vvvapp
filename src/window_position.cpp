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

#include <wx/gdicmn.h>
#include "window_position.h"
#include "utils.h"

void CWindowPosition::SavePosition( void ) {

	wxASSERT( window != NULL );

	wxConfigBase *pConfig = wxConfigBase::Get();
	if ( pConfig == NULL )
		return;

	int x, y, w, h;
	window->GetClientSize(&w, &h);
	window->GetPosition(&x, &y);
	wxString path = wxT("/WindowsLayout/" + CUtils::long2string(window->GetId()));
	pConfig->SetPath( path );
	pConfig->Write(wxT("x"), (long) x);
	pConfig->Write(wxT("y"), (long) y);
	pConfig->Write(wxT("w"), (long) w);
	pConfig->Write(wxT("h"), (long) h);
}


void CWindowPosition::RestorePosition( void ) {

	wxASSERT( window != NULL );

	wxConfigBase *pConfig = wxConfigBase::Get();
	if ( pConfig == NULL )
		return;

	wxString path = wxT("/WindowsLayout/" + CUtils::long2string(window->GetId()));
	pConfig->SetPath( path );

	int x = pConfig->Read(wxT("x"), -1),
		y = pConfig->Read(wxT("y"), -1),
		w = pConfig->Read(wxT("w"), -1),
		h = pConfig->Read(wxT("h"), -1);
	
	if( x == -1 || y == -1 || w == -1 || h == -1 ) return;

	// check to see if the window is visible in the screen
	int dw, dh;
	wxDisplaySize( &dw, &dh );
	if( x > (dw - 200) ) return;
	if( y > (dh - 200) ) return;

	// move and resize the window
	window->Move(x, y);
	window->SetClientSize(w, h);

}


