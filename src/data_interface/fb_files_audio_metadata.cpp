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
#include "firebird_db.h"
#include "../ibpp/core/ibpp.h"

using namespace IBPP;

wxString CFilesAudioMetadata::String2SQL( wxString s ) {
	wxString retVal;
	if( s == wxEmptyString ) 
		retVal = wxT("NULL");
	else
		retVal = wxT("'") + ExpandSingleQuotes(s) + wxT("'");
	return retVal;
}

wxString CFilesAudioMetadata::Long2SQL( long num ) {
	wxString retVal;
	if( num == 0 ) 
		retVal = wxT("NULL");
	else
		retVal = CUtils::long2string(num);
	return retVal;
}
	


// add this record to the database
void CFilesAudioMetadata::FB_DbInsert(void) {

	wxString sql;

	wxASSERT( !FileID.IsNull() );
	
	sql = wxT("INSERT INTO FILES_AUDIO_METADATA (FILE_ID, TRACK_TITLE, TRACK_ARTIST, TRACK_ALBUM, TRACK_YEAR, TRACK_COMMENT, TRACK_NUMBER, TRACK_GENRE, TRACK_BITRATE, TRACK_SAMPLE_RATE, TRACK_CHANNELS, TRACK_LENGTH) VALUES (");
	sql += CUtils::long2string(FileID) + wxT(", ") +
	       String2SQL(Title.Left(100)) + wxT(", ") + 
	       String2SQL(Artist.Left(100)) + wxT(", ") + 
	       String2SQL(Album.Left(100)) + wxT(", ") + 
		   Long2SQL( Year ) + wxT(", ") + 
	       String2SQL(Comment.Left(500)) + wxT(", ") + 
		   Long2SQL( Number ) + wxT(", ") + 
	       String2SQL(Genre.Left(100)) + wxT(", ") + 
		   Long2SQL( Bitrate ) + wxT(", ") + 
		   Long2SQL( SampleRate ) + wxT(", ") + 
		   Long2SQL( Channels ) + wxT(", ") + 
		   Long2SQL( Length ) + wxT(")");
	FB_ExecuteQueryNoReturn( sql );
}


// not used
void CFilesAudioMetadata::FB_DbUpdate(void) {
}

void CFilesAudioMetadata::FB_DbDelete(void)
{
	wxString sql;

	sql = wxT("DELETE FROM FILES_AUDIO_METADATA WHERE FILE_ID = ") + CUtils::long2string( FileID );
	FB_ExecuteQueryNoReturn( sql );
}

void CFilesAudioMetadata::FB_FetchRow(void) {
	int64_t tmp;
	string stmp;
	Timestamp ts;

	if( FB_st->Fetch() ) {
		// fetches a record
		eof = false;
		FB_st->Get("FILE_ID", tmp);
		FileID = (long) tmp;
		Artist = FB_st->Get( "TRACK_ARTIST", stmp ) ? wxEmptyString : CUtils::DBstd2wx( stmp );
		Album = FB_st->Get( "TRACK_ALBUM", stmp ) ? wxEmptyString : CUtils::DBstd2wx( stmp );
		Title = FB_st->Get( "TRACK_TITLE", stmp ) ? wxEmptyString : CUtils::DBstd2wx( stmp );
		Year = FB_st->Get( "TRACK_YEAR", tmp ) ? 0 : (int) tmp;
		Comment = FB_st->Get( "TRACK_COMMENT", stmp ) ? wxEmptyString : CUtils::DBstd2wx( stmp );
		Number = FB_st->Get( "TRACK_NUMBER", tmp ) ? 0 : (int) tmp;
		Genre = FB_st->Get( "TRACK_GENRE", stmp ) ? wxEmptyString : CUtils::std2wx( stmp );
		Bitrate = FB_st->Get( "TRACK_BITRATE", tmp ) ? 0 : (int) tmp;
		SampleRate = FB_st->Get( "TRACK_SAMPLE_RATE", tmp ) ? 0 : (int) tmp;
		Channels = FB_st->Get( "TRACK_CHANNELS", tmp ) ? 0 : (int) tmp;
		Length = FB_st->Get( "TRACK_LENGTH", tmp ) ? 0 : (int) tmp;
	}
	else {
		// end of the rowset
		eof = true;
		if( !TransactionAlreadyStarted ) {
			CFirebirdDB* db = (CFirebirdDB*) CBaseDB::GetDatabase();
			db->TransactionCommit();
		}
		TransactionAlreadyStarted = false;
	}
}

