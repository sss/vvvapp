/*
	This file is part of VVV (Virtual Volumes View)

	Copyright (C) 2010, the VVV Development team

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

#include "decode_search_string.h"
#include "utils.h"
#include "data_interface/base_rec.h"

#include <wx/tokenzr.h>

enum TSearchStyle {
	ssNormal,
	ssRequired,
	ssExcluded
};


CDecodeSearchString::CDecodeSearchString( const wxString& searchText )
{
	m_SearchText = searchText;
}

size_t CDecodeSearchString::SkipSpaces( const wxString& s, size_t posIni )
{
	size_t lastPos = s.Len() - 1;	// last valid index in the string
	size_t pos = posIni;
	while( pos <= lastPos ) {
		if( !wxIsspace(s[pos]) )
			return pos;
		pos++;
	}
	// here if we have gone past the end
	return pos;
}

size_t CDecodeSearchString::FindWord( const wxString& s, size_t posIni )
{
	size_t lastPos = s.Len() - 1;	// last valid index in the string
	size_t pos = posIni;
	while( pos <= lastPos ) {
		if( wxIsspace(s[pos]) )
			break;
		pos++;
	}
	return pos - 1;
}

size_t CDecodeSearchString::FindSentence( const wxString& s, size_t posIni )
{
	size_t lastPos = s.Len() - 1;	// last valid index in the string
	size_t pos = posIni + 1;		// first char of the sentence (skip '"')
	while( pos <= lastPos ) {
		if( s[pos] == _T('"') ) {
			if( pos == lastPos ) {
				// string end
				return pos;
			}
			else {
				// check for a trailing space
				if( wxIsspace(s[pos + 1]) ) {
					return pos;
				}
			}
		}
		pos++;
	}
	// here if we have gone past the end
	return pos;
}

bool CDecodeSearchString::DecodeString()
{
	TSearchStyle searchStyle = ssNormal;

	m_NormalStrings.clear();
	m_RequiredStrings.clear();
	m_ExcludedStrings.clear();
	
	wxString sep = wxT(" ");
	size_t pos = 0;	// current position in the string
	size_t lastPos = m_SearchText.Len() - 1;	// last valid index in the string

	// skip leading white spaces
	pos = SkipSpaces( m_SearchText, pos );
	
	while( pos <= lastPos ) {
		
		// check for '+' (required string)
		if( m_SearchText[pos] == _T('+') ) {
			if( pos == lastPos ) {
				// invalid string
				return false;
			}
			else {
				searchStyle = ssRequired;
				pos++;
				continue;
			}
		}
		// check for '-' (excluded string)
		if( m_SearchText[pos] == _T('-') ) {
			if( pos == lastPos ) {
				// invalid string
				return false;
			}
			else {
				searchStyle = ssExcluded;
				pos++;
				continue;
			}
		}

		wxString token = wxEmptyString;
		if( m_SearchText[pos] == _T('"') ) {
			// look for a sentence
			size_t newPos = FindSentence( m_SearchText, pos );
			if( pos > lastPos ) return false;	// uncorrect string
			size_t len = newPos - pos - 1;
			if( len > 0 ) {
				// not an empty string
				token.assign( m_SearchText, pos + 1, len );
			}
			pos = newPos + 1;
		}
		else {
			// look for a single word
			size_t newPos = FindWord( m_SearchText, pos );
			size_t len = newPos - pos + 1;
			token.assign( m_SearchText, pos, len );
			pos = newPos + 1;
		}

		if( !token.IsEmpty() ) {
			switch( searchStyle ) {
				case ssNormal:
					m_NormalStrings.push_back( token );
					break;
				case ssRequired:
					m_RequiredStrings.push_back( token );
					break;
				case ssExcluded:
					m_ExcludedStrings.push_back( token );
					break;
			}
		}
		searchStyle = ssNormal;

		pos = SkipSpaces( m_SearchText, pos );
	}

	return true;
}

wxString CDecodeSearchString::AddWildcards( const wxString &s, CMainFrame::FilenameSearchKind fsk )
{
	wxString retVal;
	switch( fsk ) {
		case CMainFrame::fskStartsWith:
			retVal = s + wxT("%");
			break;
		case CMainFrame::fskContains:
			retVal = wxT("%") + s + wxT("%");
			break;
		default:
			retVal = s;
			break;
	}
	return retVal;
}

wxString CDecodeSearchString::ProcessOneContainer( const wxString& columnName, std::vector <wxString> container, CMainFrame::FilenameSearchKind fsk, wxString connector, bool negate )
{
	std::vector <wxString>::iterator iter;
	wxString retVal = wxEmptyString;
	wxString colName = wxT("UPPER(") + columnName + wxT(")");

	for( iter = container.begin(); iter != container.end(); iter++ ) {
		wxString s = wxEmptyString;
		if( negate )
			s += wxT("NOT ");
		s += colName;
		if( fsk == CMainFrame::fskIsEqual )
			s += wxT(" = '" );
		else
			s += wxT(" LIKE '" );
		wxString stmp = CUtils::ExpandSingleQuotes( *iter );
		stmp = CBaseRec::EscapeWildcards( stmp, wxT("/") );
		stmp = AddWildcards( stmp, fsk );
		s += stmp;
		if( fsk == CMainFrame::fskIsEqual )
			s += wxT("'" );
		else
			s += wxT("' ESCAPE '/'" );
		if( !retVal.IsEmpty() ) 
			retVal += connector;
		retVal += wxT( "(" ) + s + wxT( ")" );
	}

	return retVal;
}

wxString CDecodeSearchString::CreateWhereClause( const wxString& columnName, CMainFrame::FilenameSearchKind fsk )
{
	wxString sNormal = wxEmptyString, sRequired = wxEmptyString, sExcluded = wxEmptyString;
	wxString wh = wxEmptyString;

	// normal strings
	sNormal = ProcessOneContainer( columnName, m_NormalStrings, fsk, wxT(" OR "), false );

	// required strings
	sRequired = ProcessOneContainer( columnName, m_RequiredStrings, fsk, wxT(" AND "), false );

	// excludeded strings
	sExcluded = ProcessOneContainer( columnName, m_ExcludedStrings, fsk, wxT(" AND "), true );

	// now create the where clause
	if( !sNormal.IsEmpty() ) {
		wh = wxT("(") + sNormal + wxT(")");
	}
	if( !sRequired.IsEmpty() ) {
		if( !wh.IsEmpty() ) {
			wh += wxT(" AND ");
		}
		wh += wxT("(") + sRequired + wxT(")");
	}
	if( !sExcluded.IsEmpty() ) {
		if( !wh.IsEmpty() ) {
			wh += wxT(" AND ");
		}
		wh += wxT("(") + sExcluded + wxT(")");
	}

	return wh;
}



