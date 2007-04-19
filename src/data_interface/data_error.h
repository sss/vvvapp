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

// a class to handle database errors

#ifndef __DATA_ERROR_H__
#define __DATA_ERROR_H__

#include <wx/string.h>
#include <exception>

using namespace std;

class CDataErrorException : public runtime_error {

public:

	// cause of the error
	enum ErrorCause { Unique, ReferentialIntegrity, Check };

	CDataErrorException( wxString errMsg, ErrorCause ec );

	// return the cause of this error
	ErrorCause GetErrorCause();

	// converts an error from Firebird error code
	// returns true if the error code is handled by this class and sets the "ec" parameter to the correct value
	// returns false and does not change "ec" if the error code is not handled
	static bool ConvertFirebirdError( long gdscode, ErrorCause& ec );

private:
	
	// the cause of this error
	ErrorCause m_ErrorCode;

};

#endif

