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

#ifndef __MYLISTITEMDATA_H__
#define __MYLISTITEMDATA_H__

#include <wx/string.h>
#include <wx/longlong.h>
#include <wx/datetime.h>

#include "data_interface/db_null.h"

// this class implements a custom class to store information about list control items

class MyListItemData {

public:

	MyListItemData( const wxString& name, const wxString& ext, wxLongLong size, wxDateTime dateTime, bool isFolder ) :
	                m_name(name), m_ext(ext), m_size(size), m_dateTime(dateTime), m_isFolder(isFolder) {}

	const wxString& GetName() const { return m_name; }
	const wxString& GetExt() const { return m_ext; }
	wxLongLong GetSize() { return m_size; }
	wxDateTime GetDateTime() { return m_dateTime; }
	bool IsFolder() { return m_isFolder; }

private:

	// data to be shown in the list control
	wxString m_name, m_ext;
	wxLongLong m_size;
	bool m_isFolder;
	wxDateTime m_dateTime;

	// database data


};

#endif
