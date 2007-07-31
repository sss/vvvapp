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
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

wxString CFilesAudioMetadata::String2SQL( wxString s ) {
	wxString retVal;
	if( s == "" ) 
		retVal = "NULL";
	else
		retVal = "'" + ExpandSingleQuotes(s) + "'";
	return retVal;
}

wxString CFilesAudioMetadata::Long2SQL( long num ) {
	wxString retVal;
	if( num == 0 ) 
		retVal = "NULL";
	else
		retVal = CUtils::long2string(num);
	return retVal;
}
	


// add this record to the database
void CFilesAudioMetadata::FB_DbInsert(void) {

	wxString sql;

	wxASSERT( !FileID.IsNull() );
	
	sql = "INSERT INTO FILES_AUDIO_METADATA (FILE_ID, TRACK_TITLE, TRACK_ARTIST, TRACK_ALBUM, TRACK_YEAR, TRACK_COMMENT, TRACK_NUMBER, TRACK_GENRE, TRACK_BITRATE, TRACK_SAMPLE_RATE, TRACK_CHANNELS, TRACK_LENGTH) VALUES (";
	sql += CUtils::long2string(FileID) + ", " +
	       String2SQL(Title) + ", " + 
	       String2SQL(Artist) + ", " + 
	       String2SQL(Album) + ", " + 
		   Long2SQL( Year ) + ", " + 
	       String2SQL(Comment) + ", " + 
		   Long2SQL( Number ) + ", " + 
	       String2SQL(Genre) + ", " + 
		   Long2SQL( Bitrate ) + ", " + 
		   Long2SQL( SampleRate ) + ", " + 
		   Long2SQL( Channels ) + ", " + 
		   Long2SQL( Length ) + ")";
	FB_ExecuteQueryNoReturn( sql );
}


// not used
void CFilesAudioMetadata::FB_DbUpdate(void) {
}

void CFilesAudioMetadata::FB_DbDelete(void)
{
	wxString sql;

	sql = "DELETE FROM FILES_AUDIO_METADATA WHERE FILE_ID = " + CUtils::long2string( FileID );
	FB_ExecuteQueryNoReturn( sql );
}

void CFilesAudioMetadata::FB_FetchRow(void) {
}

