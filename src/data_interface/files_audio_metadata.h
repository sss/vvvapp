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

#ifndef __FILES_AUDIO_METADATA_H__
#define __FILES_AUDIO_METADATA_H__

#include <wx/string.h>
#include "base_rec.h"

class CFilesAudioMetadata : public CBaseRec
{
public:
	CFilesAudioMetadata(void);
	~CFilesAudioMetadata(void);

	// reads the audio metadata for a file. FileID is in this->FileID
	// returns true if the record is found and sets the fields of this instance
	// returns false if the record is not found
	bool DBReadMetadata();

	// data members ----------------------------
	CNullableLong FileID;	// primary key
	wxString Title, Artist, Album, Comment, Genre;
	int Year, Number, Bitrate, Channels;
	int Length;	// in seconds
	int SampleRate;	// hertz

protected:

	// Firebird implementation of the database methods
	void FB_DbInsert(void);
	void FB_DbUpdate(void);
	void FB_DbDelete(void);
	void FB_FetchRow(void);

	// converts a string to a value to be used in a SQL string. Filters empty string to NULL
	wxString String2SQL( wxString s );
	// converts a long to a value to be used in a SQL string. Filters 0 to NULL
	wxString Long2SQL( long num );


};


#endif
