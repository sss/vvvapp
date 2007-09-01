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

#include "audio_metadata.h"
#include <id3/tag.h>



bool CAudioMetadata::ReadMP3Metadata( wxString fileName, CFilesAudioMetadata& metaData ) {
	char *str1 = new char[1024];
	bool found = false;

	ID3_Tag myTag( fileName.c_str() );

	ID3_Frame* myFrame = myTag.Find(ID3FID_LEADARTIST);
	if( myFrame != NULL ) {
		ID3_Field* myField = myFrame->GetField(ID3FN_TEXT);
		if( myField != NULL ) {
			myField->Get(str1, 1024);
			metaData.Artist = str1;
			found = true;
		}
	}

	myFrame = myTag.Find(ID3FID_TITLE);
	if( myFrame != NULL ) {
		ID3_Field* myField = myFrame->GetField(ID3FN_TEXT);
		if( myField != NULL ) {
			myField->Get(str1, 1024);
			metaData.Title = str1;
			found = true;
		}
	}

	myFrame = myTag.Find(ID3FID_ALBUM);
	if( myFrame != NULL ) {
		ID3_Field* myField = myFrame->GetField(ID3FN_TEXT);
		if( myField != NULL ) {
			myField->Get(str1, 1024);
			metaData.Album = str1;
			found = true;
		}
	}

	myFrame = myTag.Find(ID3FID_COMMENT);
	if( myFrame != NULL ) {
		ID3_Field* myField = myFrame->GetField(ID3FN_TEXT);
		if( myField != NULL ) {
			myField->Get(str1, 1024);
			metaData.Comment = str1;
			found = true;
		}
	}

	myFrame = myTag.Find(ID3FID_TRACKNUM);
	if( myFrame != NULL ) {
		ID3_Field* myField = myFrame->GetField(ID3FN_TEXT);
		if( myField != NULL ) {
			myField->Get(str1, 1024);
			// handles the "5/9" case
			wxString s = str1;
			s = s.BeforeFirst( '/' );
			long tmp;
			if( s.ToLong( &tmp ) )
				metaData.Number = tmp;
			else
				metaData.Number = 0;
			found = true;
		}
	}

	myFrame = myTag.Find(ID3FID_YEAR);
	if( myFrame != NULL ) {
		ID3_Field* myField = myFrame->GetField(ID3FN_TEXT);
		if( myField != NULL ) {
			myField->Get(str1, 1024);
			long tmp;
			wxString s = str1;
			if( s.ToLong( &tmp ) )
				metaData.Year = tmp;
			else
				metaData.Year = 0;
			found = true;
		}
	}

	myFrame = myTag.Find(ID3FID_CONTENTTYPE);
	if( myFrame != NULL ) {
		ID3_Field* myField = myFrame->GetField(ID3FN_TEXT);
		if( myField != NULL ) {
			myField->Get(str1, 1024);
			wxString s = str1;
			if( s[0] == '(' ) {
				// decodes genre
				s = s.AfterFirst( '(' );
				s = s.BeforeFirst( ')' );
				long i;
				if( s.ToLong(&i) ) {
					const char *cp = ID3_V1GENRE2DESCRIPTION(i);
					if( cp != NULL )
						metaData.Genre = cp;
				}
			}
			else
				metaData.Genre = s;
			found = true;
		}
	}

	const Mp3_Headerinfo* mp3info;
	mp3info = myTag.GetMp3HeaderInfo();
	if( mp3info != NULL ) {
		metaData.Bitrate = mp3info->bitrate / 1000;
		metaData.SampleRate = mp3info->frequency;
		metaData.Length = mp3info->time;
		if( mp3info->channelmode == MP3CHANNELMODE_FALSE ) {
			metaData.Channels = 0;
		}
		else {
			if( mp3info->channelmode == MP3CHANNELMODE_SINGLE_CHANNEL ) {
				metaData.Channels = 1;
			}
			else {
				metaData.Channels = 2;
			}
		}
		found = true;
	}

	delete str1;

	return found;
}

