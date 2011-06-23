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

#include <fileref.h>
#include <tag.h>

static wxString TagLibString2wx( const TagLib::String &ts )
{
	std::string s = ts.to8Bit( true );
	wxString ws = CUtils::std2wx( s, &wxConvUTF8 );
	return ws;
}


bool CAudioMetadata::ReadMP3Metadata( wxString fileName, CFilesAudioMetadata& metaData ) {

	bool found = false;

	TagLib::FileRef f( fileName.fn_str() );

	if( f.isNull() ) return false;

	if( f.tag() ) {
		wxString s;
		TagLib::uint i;

		TagLib::Tag *tag = f.tag();

		s = TagLibString2wx( tag->artist() );
		if( !s.IsEmpty() ) {
			metaData.Artist = s;
			found = true;
		}
		s = TagLibString2wx( tag->title() );
		if( !s.IsEmpty() ) {
			metaData.Title = s;
			found = true;
		}
		s = TagLibString2wx( tag->album() );
		if( !s.IsEmpty() ) {
			metaData.Album = s;
			found = true;
		}
		s = TagLibString2wx( tag->comment() );
		if( !s.IsEmpty() ) {
			metaData.Comment = s;
			found = true;
		}
		i = tag->track();
		if( i != 0 ) {
			metaData.Number = i;
			found = true;
		}
		i = tag->year();
		if( i != 0 ) {
			metaData.Year = i;
			found = true;
		}
		s = TagLibString2wx( tag->genre() );
		if( !s.IsEmpty() ) {
			metaData.Genre = s;
			found = true;
		}
	}

	if( f.audioProperties() ) {
		TagLib::AudioProperties *properties = f.audioProperties();
		int i;
		i = properties->bitrate();
		if( i != 0 ) {
			metaData.Bitrate = i;
			found = true;
		}
		i = properties->sampleRate();
		if( i != 0 ) {
			metaData.SampleRate = i;
			found = true;
		}
		i = properties->length();
		if( i != 0 ) {
			metaData.Length = i;
			found = true;
		}
		i = properties->channels();
		if( i != 0 ) {
			metaData.Channels = i;
			found = true;
		}

	}

	return found;
}

