/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2007-2008, the VVV Development team

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

#include "utils.h"
#include "ibpp.h"
#include <wx/string.h>
#include "wx/datetime.h"
#include <string>

using namespace IBPP;

wxString ExpandSingleQuotes( wxString txt ) {
	// doubles single-quote characters in a string, used to create SQL statements

	txt.Replace( wxT("'"), wxT("''"), true );
	return txt;
}


wxString String2SQL( wxString s ) {
	wxString retVal;
	if( s == wxEmptyString ) 
		retVal = wxT("NULL");
	else
		retVal = wxT("'") + ExpandSingleQuotes(s) + wxT("'");
	return retVal;
}

wxString Long2SQL( long num ) {
	wxString retVal;
	if( num == 0 ) 
		retVal = wxT("NULL");
	else
		retVal = CUtils::long2string(num);
	return retVal;
}


void CopyGenerator( Database dbIn, Database dbOut, wxString generatorName ) {
	wxString sql;
	int64_t tmp;
	long genValue;

	Transaction trIn = TransactionFactory( dbIn );
	Transaction trOut = TransactionFactory( dbOut );

	trIn->Start();
	trOut->Start();

	Statement stIn = StatementFactory( dbIn, trIn );
	Statement stOut = StatementFactory( dbOut, trOut );

	sql = wxT("SELECT GEN_ID(") + generatorName + wxT(", 0) AS NEW_ID FROM RDB$DATABASE");
	stIn->Execute( CUtils::DBwx2std(sql) );
	stIn->Fetch();
	stIn->Get("NEW_ID", tmp);
	genValue = (long) tmp;

	sql = wxT("SET GENERATOR ") + generatorName + wxT(" TO ") + CUtils::long2string(genValue);
	stOut->Execute( CUtils::DBwx2std(sql) );

	trIn->Commit();
	trOut->Commit();
}



void CopyVolumes( Database dbIn, Database dbOut ) {

	Transaction trIn = TransactionFactory( dbIn );
	Transaction trOut = TransactionFactory( dbOut );

	trIn->Start();
	trOut->Start();

	Statement stIn = StatementFactory( dbIn, trIn );
	stIn->Execute( "SELECT * FROM VOLUMES ORDER BY VOLUME_ID" );

	Statement stOut = StatementFactory( dbOut, trOut );

	while( stIn->Fetch() ) {
		int64_t tmp;
		std::string stmp;
		long VolumeID;
		wxString VolumeDescription, VolumeName;

		stIn->Get("VOLUME_ID", tmp);
		VolumeID = (long) tmp;
		stIn->Get( "VOLUME_NAME", stmp );
		VolumeName = CUtils::std2wx( stmp );
		if( stIn->IsNull("VOLUME_DESCRIPTION") ) {
			VolumeDescription = wxEmptyString;
		}
		else {
			// reads the blob
			Blob bl = BlobFactory( dbIn, trIn );
			std::string s;
			stIn->Get( "VOLUME_DESCRIPTION", bl );
			bl->Load( s );
			VolumeDescription = CUtils::std2wx( s );
		}

		wxString sql;
		if( VolumeDescription.empty() )
			sql = wxT("INSERT INTO VOLUMES (VOLUME_ID, VOLUME_NAME) VALUES (") +  CUtils::long2string(VolumeID) + wxT(", '") + ExpandSingleQuotes(VolumeName) + wxT("')");
		else
			sql = wxT("INSERT INTO VOLUMES (VOLUME_ID, VOLUME_NAME, VOLUME_DESCRIPTION) VALUES (") +  CUtils::long2string(VolumeID) + wxT(", '") + ExpandSingleQuotes(VolumeName) + wxT("', '") + ExpandSingleQuotes(VolumeDescription) + wxT("')");

		stOut->Execute( CUtils::DBwx2std(sql) );
	}

	trIn->Commit();
	trOut->Commit();
}


void CopyPaths( Database dbIn, Database dbOut ) {

	int nRows = 0;

	Transaction trIn = TransactionFactory( dbIn );
	Transaction trOut = TransactionFactory( dbOut );

	trIn->Start();
	trOut->Start();

	Statement stIn = StatementFactory( dbIn, trIn );
	stIn->Execute( "SELECT * FROM PATHS ORDER BY PATH_ID" );

	Statement stOut = StatementFactory( dbOut, trOut );

	while( stIn->Fetch() ) {
		int64_t tmp;
		std::string stmp;
		
		wxString PathName, PathDescription;
		long FatherID, PathID, VolumeID;

		stIn->Get( "PATH_NAME", stmp );
		PathName = CUtils::std2wx( stmp );
		stIn->Get("PATH_ID", tmp);
		PathID = (long) tmp;
		stIn->Get("VOLUME_ID", tmp);
		VolumeID = (long) tmp;
		if( stIn->IsNull("FATHER_ID") )
			FatherID = -1;
		else {
			stIn->Get("FATHER_ID", tmp);
			FatherID = (long) tmp;
		}
		if( stIn->IsNull("PATH_DESCRIPTION") ) {
			PathDescription = wxEmptyString;
		}
		else {
			stIn->Get( "PATH_DESCRIPTION", stmp );
			PathDescription = CUtils::std2wx( stmp );
		}

		wxString sql;
		sql = wxT("INSERT INTO PATHS (");
		sql += wxT("PATH_ID, ");
		sql += wxT("VOLUME_ID, PATH_NAME, FATHER_ID, PATH_DESCRIPTION) VALUES (");
		sql += CUtils::long2string(PathID) + wxT(", ");
		sql += CUtils::long2string(VolumeID) + wxT(", '") + ExpandSingleQuotes(PathName) + wxT("', ");
		if( FatherID < 0 )
			sql += wxT("NULL");
		else
			sql += CUtils::long2string(FatherID);
		if( !PathDescription.empty() )
			sql += wxT(", '") + ExpandSingleQuotes(PathDescription) + wxT("'");
		else
			sql += wxT(", NULL");
		sql += wxT(")");

		stOut->Execute( CUtils::DBwx2std(sql) );

		nRows++;
		if( nRows > 5000 ) {
			trOut->Commit();
			trOut->Start();
			nRows = 0;
		}

	}

	trIn->Commit();
	trOut->Commit();

}


void CopyFiles( Database dbIn, Database dbOut ) {
	int nRows = 0;

	Transaction trIn = TransactionFactory( dbIn );
	Transaction trOut = TransactionFactory( dbOut );

	trIn->Start();
	trOut->Start();

	Statement stIn = StatementFactory( dbIn, trIn );
	stIn->Execute( "SELECT * FROM FILES ORDER BY FILE_ID" );

	Statement stOut = StatementFactory( dbOut, trOut );

	while( stIn->Fetch() ) {
		int64_t tmp;
		std::string stmp;
		Timestamp ts;
		
		wxString FileName, FileDescription, FileExt;
		wxLongLong FileSize;
		long FileID, PathFileID, PathID;
		wxDateTime DateTime;

		stIn->Get("FILE_ID", tmp);
		FileID = (long) tmp;
		stIn->Get( "FILE_NAME", stmp );
		FileName = CUtils::std2wx( stmp );
		stIn->Get( "FILE_EXT", stmp );
		FileExt = CUtils::std2wx( stmp );
		stIn->Get("FILE_SIZE", tmp);
		FileSize = (wxLongLong) tmp;
		stIn->Get("FILE_DATETIME", ts);
		DateTime.Set( ts.Day(), (wxDateTime::Month) (wxDateTime::Jan + ts.Month() - 1), ts.Year(), ts.Hours(), ts.Minutes(), ts.Seconds() );
		if( stIn->IsNull("PATH_FILE_ID") )
			PathFileID = -1;
		else {
			stIn->Get("PATH_FILE_ID", tmp);
			PathFileID = (long) tmp;
		}
		if( stIn->IsNull("PATH_ID") )
			PathID = -1;
		else {
			stIn->Get("PATH_ID", tmp);
			PathID = (long) tmp;
		}
		if( stIn->IsNull("FILE_DESCRIPTION") ) {
			FileDescription = wxEmptyString;
		}
		else {
			stIn->Get( "FILE_DESCRIPTION", stmp );
			FileDescription = CUtils::std2wx( stmp );
		}

		wxString sql;
		sql = wxT("INSERT INTO FILES (");
		sql += wxT("FILE_ID, ");
		sql += wxT("FILE_NAME, FILE_EXT, FILE_SIZE, FILE_DATETIME, PATH_FILE_ID, PATH_ID, FILE_DESCRIPTION) VALUES (");
		sql += CUtils::long2string(FileID) + wxT(", ");
		sql += wxT("'") + ExpandSingleQuotes(FileName) + wxT("', '") + 
					ExpandSingleQuotes(FileExt) + wxT("', ") + 
					FileSize.ToString() + wxT(", ") +
					DateTime.Format( wxT("'%Y-%m-%d %H:%M:%S'") ) + wxT(", ") +
					(PathFileID < 0 ? wxT("NULL") : CUtils::long2string(PathFileID) ) + wxT(", ") +
					(PathID < 0 ?  wxT("NULL") : CUtils::long2string(PathID) ) + wxT(", ") +
					(FileDescription.empty() ? wxT("NULL") : wxT("'") + ExpandSingleQuotes(FileDescription) + wxT("'")) +
					wxT(")");

		stOut->Execute( CUtils::DBwx2std(sql) );

		nRows++;
		if( nRows > 5000 ) {
			trOut->Commit();
			trOut->Start();
			nRows = 0;
		}

	}

	trIn->Commit();
	trOut->Commit();

}


void CopyFilesAudioMetadata( Database dbIn, Database dbOut ) {
	int nRows = 0;

	Transaction trIn = TransactionFactory( dbIn );
	Transaction trOut = TransactionFactory( dbOut );

	trIn->Start();
	trOut->Start();

	Statement stIn = StatementFactory( dbIn, trIn );
	stIn->Execute( "SELECT * FROM FILES_AUDIO_METADATA ORDER BY FILE_ID" );

	Statement stOut = StatementFactory( dbOut, trOut );

	while( stIn->Fetch() ) {
		int64_t tmp;
		std::string stmp;

		long FileID;
		wxString Artist, Title, Album, Comment, Genre;
		int Bitrate, SampleRate, Channels, Length, Year, Number;

		stIn->Get("FILE_ID", tmp);
		FileID = (long) tmp;
		Artist = wxEmptyString;
		Album = wxEmptyString;
		Title = wxEmptyString;
		Comment = wxEmptyString;
		Genre = wxEmptyString;
		if( !stIn->IsNull("TRACK_ARTIST") ) {
			stIn->Get( "TRACK_ARTIST", stmp );
			Artist = CUtils::std2wx( stmp );
		}
		if( !stIn->IsNull("TRACK_ALBUM") ) {
			stIn->Get( "TRACK_ALBUM", stmp );
			Album = CUtils::std2wx( stmp );
		}
		if( !stIn->IsNull("TRACK_TITLE") ) {
			stIn->Get( "TRACK_TITLE", stmp );
			Title = CUtils::std2wx( stmp );
		}
		Year = stIn->Get( "TRACK_YEAR", tmp ) ? 0 : (int) tmp;
		if( !stIn->IsNull("TRACK_COMMENT") ) {
			stIn->Get( "TRACK_COMMENT", stmp );
			Comment = CUtils::std2wx( stmp );
		}
		Number = stIn->Get( "TRACK_NUMBER", tmp ) ? 0 : (int) tmp;
		if( !stIn->IsNull("TRACK_GENRE") ) {
			stIn->Get( "TRACK_GENRE", stmp );
			Genre = CUtils::std2wx( stmp );
		}
		Bitrate = stIn->Get( "TRACK_BITRATE", tmp ) ? 0 : (int) tmp;
		SampleRate = stIn->Get( "TRACK_SAMPLE_RATE", tmp ) ? 0 : (int) tmp;
		Channels = stIn->Get( "TRACK_CHANNELS", tmp ) ? 0 : (int) tmp;
		Length = stIn->Get( "TRACK_LENGTH", tmp ) ? 0 : (int) tmp;

		wxString sql;
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

		stOut->Execute( CUtils::DBwx2std(sql) );

		nRows++;
		if( nRows > 5000 ) {
			trOut->Commit();
			trOut->Start();
			nRows = 0;
		}

	}

	trIn->Commit();
	trOut->Commit();

}


void CopyVirtualPaths( Database dbIn, Database dbOut ) {

	int nRows = 0;

	Transaction trIn = TransactionFactory( dbIn );
	Transaction trOut = TransactionFactory( dbOut );

	trIn->Start();
	trOut->Start();

	Statement stIn = StatementFactory( dbIn, trIn );
	stIn->Execute( "SELECT * FROM VIRTUAL_PATHS ORDER BY PATH_ID" );

	Statement stOut = StatementFactory( dbOut, trOut );

	while( stIn->Fetch() ) {
		int64_t tmp;
		std::string stmp;
		
		wxString PathName;
		long FatherID, PathID, PhysPathID;

		stIn->Get( "PATH", stmp );
		PathName = CUtils::std2wx( stmp );
		stIn->Get("PATH_ID", tmp);
		PathID = (long) tmp;
		if( stIn->IsNull("FATHER_ID") )
			FatherID = -1;
		else {
			stIn->Get("FATHER_ID", tmp);
			FatherID = (long) tmp;
		}
		if( stIn->IsNull("PHYS_PATH_ID") )
			PhysPathID = -1;
		else {
			stIn->Get("PHYS_PATH_ID", tmp);
			PhysPathID = (long) tmp;
		}


		wxString sql;
		sql = wxT("INSERT INTO VIRTUAL_PATHS (PATH_ID, PATH, FATHER_ID, PHYS_PATH_ID) VALUES ( ");
		sql += CUtils::long2string(PathID) + wxT(", '");
		sql += ExpandSingleQuotes(PathName) + wxT("', ");
		if( FatherID < 0 )
			sql += wxT("NULL");
		else
			sql += CUtils::long2string(FatherID);
		sql += wxT(", ");
		if( PhysPathID < 0 )
			sql += wxT("NULL");
		else
			sql += CUtils::long2string(PhysPathID);
		sql += wxT(")");

		stOut->Execute( CUtils::DBwx2std(sql) );

		nRows++;
		if( nRows > 5000 ) {
			trOut->Commit();
			trOut->Start();
			nRows = 0;
		}

	}

	trIn->Commit();
	trOut->Commit();

}


void CopyVirtualFiles( Database dbIn, Database dbOut ) {
	int nRows = 0;

	Transaction trIn = TransactionFactory( dbIn );
	Transaction trOut = TransactionFactory( dbOut );

	trIn->Start();
	trOut->Start();

	Statement stIn = StatementFactory( dbIn, trIn );
	stIn->Execute( "SELECT * FROM VIRTUAL_FILES ORDER BY FILE_ID" );

	Statement stOut = StatementFactory( dbOut, trOut );

	while( stIn->Fetch() ) {
		int64_t tmp;
		std::string stmp;
		
		long FileID, PhysicalFileID, VirtualPathID, VirtualPathFileID;

		stIn->Get("FILE_ID", tmp);
		FileID = (long) tmp;
		stIn->Get("VIRTUAL_PATH_ID", tmp);
		VirtualPathID = (long) tmp;
		stIn->Get("PHYSICAL_FILE_ID", tmp);
		PhysicalFileID = (long) tmp;
		if( stIn->IsNull("VIRTUAL_PATH_FILE_ID") )
			VirtualPathFileID = -1;
		else {
			stIn->Get("VIRTUAL_PATH_FILE_ID", tmp);
			VirtualPathFileID = (long) tmp;
		}

		wxString sql;

		sql = wxT("INSERT INTO VIRTUAL_FILES (");
		sql += wxT("FILE_ID, ");
		sql += wxT("VIRTUAL_PATH_ID, PHYSICAL_FILE_ID, VIRTUAL_PATH_FILE_ID) VALUES (");
		sql += CUtils::long2string(FileID) + wxT(", ");
		sql += CUtils::long2string(VirtualPathID) + wxT(", ") + 
			CUtils::long2string(PhysicalFileID) + wxT(", ") +
		(VirtualPathFileID < 0 ? wxT("NULL") : CUtils::long2string(VirtualPathFileID) ) + wxT(")");

		stOut->Execute( CUtils::DBwx2std(sql) );

		nRows++;
		if( nRows > 5000 ) {
			trOut->Commit();
			trOut->Start();
			nRows = 0;
		}

	}

	trIn->Commit();
	trOut->Commit();

}




void CUtils::ConvertDbToUnicode( wxString oldDB, wxString newDB ) {

	CUtils::MsgInfo( _("Conversion is about to start: a message will tell you when it will be completed.") );
	wxBusyCursor wait;
	wxSafeYield();

	Database dbIn = DatabaseFactory( "", wx2std(oldDB), "SYSDBA", "masterkey" );
	Database dbOut = DatabaseFactory( "", wx2std(newDB), "SYSDBA", "masterkey" );

	dbIn->Connect();
	dbOut->Connect();

	CopyVolumes( dbIn, dbOut );
	CopyPaths( dbIn, dbOut );
	CopyFiles( dbIn, dbOut );
	CopyFilesAudioMetadata( dbIn, dbOut );
	CopyVirtualPaths( dbIn, dbOut );
	CopyVirtualFiles( dbIn, dbOut );

	CopyGenerator( dbIn, dbOut, wxT("GEN_FILES_ID") );
	CopyGenerator( dbIn, dbOut, wxT("GEN_PATHS_ID") );
	CopyGenerator( dbIn, dbOut, wxT("GEN_VIRTUAL_FILES_ID") );
	CopyGenerator( dbIn, dbOut, wxT("GEN_VIRTUAL_PATHS_ID") );
	CopyGenerator( dbIn, dbOut, wxT("GEN_VOLUMES_ID") );

	dbIn->Disconnect();
	dbOut->Disconnect();

	CUtils::MsgInfo( _("Conversion completed") );

}
