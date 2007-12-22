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

#include "files_audio_metadata.h"

CFilesAudioMetadata::CFilesAudioMetadata(void)
{
	Title = Artist = Album = Comment = Genre = "";
	Year = Number = Bitrate = SampleRate = Length = Channels = 0;
}

bool CFilesAudioMetadata::DBReadMetadata() {
	wxString sql = "SELECT * FROM FILES_AUDIO_METADATA WHERE FILE_ID = " + CUtils::long2string(FileID);
	DBStartMultiRowQuery( sql, true );
	return !this->IsEOF();
}




CFilesAudioMetadata::~CFilesAudioMetadata(void)
{
}
