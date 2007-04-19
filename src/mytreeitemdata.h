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

#ifndef __MYTREEITEMDATA_H__
#define __MYTREEITEMDATA_H__

// this class implements a custom ItemData class to store information about tree control items

#include "wx/treectrl.h"

class MyTreeItemData : public wxTreeItemData {
public:
	MyTreeItemData( const wxString& desc, long VolumeID, long PathID, bool IsVolume ) : 
	                m_desc(desc), m_VolumeID(VolumeID), m_PathID(PathID), m_IsVolume(IsVolume), m_AlreadyOpened(false) {}
	const wxString& GetDesc() const { return m_desc; }
	long GetVolumeID(void) { return m_VolumeID; }
	long GetPathID(void) { return m_PathID; }
	bool IsVolume(void) { return m_IsVolume; }
	bool AlreadyOpened(void) { return m_AlreadyOpened; }
	void SetAlreadyOpened(void) { m_AlreadyOpened = true; }
private:
	wxString m_desc;
	long m_VolumeID, m_PathID;	// m_VolumeID is not used for the virtual folders tree
	bool m_IsVolume;	// true if this node is a volume and not a folder
	bool m_AlreadyOpened;	// true if this node has already been opened
};

#endif
