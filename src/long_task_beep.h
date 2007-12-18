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

#ifndef __LONG_TASK_BEEP_H__
#define __LONG_TASK_BEEP_H__

/*
this is a class that used to make a beep sound at the end of a task that takes
more than a certain time complete
*/

#include <wx/utils.h>
#include <wx/datetime.h>

class CLongTaskBeep {

public:

	CLongTaskBeep();
	~CLongTaskBeep();

	// catt this function to disable bell playing
	void DoNotPlayBell();

	// sets the minimun time before ringing the bell
	static void SetMinSecondsForBell( int nSeconds );

private:

	wxDateTime start;

	bool doPlayBell;

	// the minimum number of seconds that the task must take to complete before ringing the bell
	static int minSecondsForBell;

};










#endif




