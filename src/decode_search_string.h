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

#ifndef __DECODE_SEARCH_STRING_H__
#define __DECODE_SEARCH_STRING_H__

/*
this is a class that decodes a search string and creates the corresponding sql WHERE clause

the search rules are the following:
if there are many words they are connected with an OR clause
a word starting with a '+' is required
a word starting with a '-' is excludes
a text included between "" is takes as is

*/

#include "mainframe.h"

#include <wx/string.h>
#include <vector>

class CDecodeSearchString {

public:

	CDecodeSearchString( const wxString& searchText );

	// return true if decoding is succesful (no errors)
	bool DecodeString();

	// return the where clause corresponding to the decoded search string
	// columnName is the name of the database column to be searched
	wxString CreateWhereClause( const wxString& columnName, CMainFrame::FilenameSearchKind fsk );

private:

	// return the index of the first position in the string that is not a space, starting from posIni included
	// return the length of the string (an invalid index) if not succesful (only spaces from here to the end of the string)
	static size_t SkipSpaces( const wxString& s, size_t posIni );

	// assumes that posIni points to the first letter of a word
	// return the position of the last letter of the word
	static size_t FindWord( const wxString& s, size_t posIni );

	// assumes that posIni points to the first '"' char specifying a sentence (for example "this is a sentence")
	// return the position on the closing '"' of the sentence on an invalid index if the sentence is not closed correctly
	static size_t FindSentence( const wxString& s, size_t posIni );

	// add wildcards as needed
	static wxString AddWildcards( const wxString &s, CMainFrame::FilenameSearchKind fsk );

	// process one of the string containers and return a sql where clause for that container
	// if negate == true put a "NOT" before each component of the container
	static wxString ProcessOneContainer( const wxString& columnName, std::vector <wxString> container, CMainFrame::FilenameSearchKind fsk, wxString connector, bool negate );

	// the search string entered by the user
	wxString m_SearchText;

	// strings to be treated as normal (connected with OR)
	std::vector <wxString> m_NormalStrings;

	// required strings
	std::vector <wxString> m_RequiredStrings;

	// excluded strings
	std::vector <wxString> m_ExcludedStrings;

};

#endif

