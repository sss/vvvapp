/*
 *  This file is part of Poedit (http://www.poedit.net)
 *
 *  Copyright (C) 2003-2006 Vaclav Slavik
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 *  $Id: chooselang.cpp 1357 2008-03-03 22:23:37Z vaclavslavik $
 *
 *  Language chooser
 *
 */

// modified for VVV

#include <wx/wxprec.h>

#include <wx/wx.h>
#include <wx/config.h>

#include "chooselang.h"
#include "utils.h"

#if NEED_CHOOSELANG_UI
static void SaveUILanguage(wxLanguage lang)
{
    if (lang == wxLANGUAGE_UNKNOWN)
        return;
	wxConfig::Get()->SetPath(wxT("/Settings"));
    if (lang == wxLANGUAGE_DEFAULT)
        wxConfig::Get()->Write(_T("ui_language"), _T("default"));
    else
        wxConfig::Get()->Write(_T("ui_language"),
                               wxLocale::GetLanguageInfo(lang)->CanonicalName);
}
#endif // NEED_CHOOSELANG_UI

wxLanguage GetUILanguage()
{
#if !NEED_CHOOSELANG_UI
    return wxLANGUAGE_DEFAULT;
#else
    wxLanguage lang(wxLANGUAGE_DEFAULT);
	wxConfig::Get()->SetPath(wxT("/Settings"));
    wxString lng = wxConfig::Get()->Read(_T("ui_language"));
    if (lng.empty())
    {
		lang = wxLANGUAGE_DEFAULT;
        //lang = ChooseLanguage();
        //if (lang != wxLANGUAGE_UNKNOWN)
        //    SaveUILanguage(lang);
        //else
        //    lang = wxLANGUAGE_DEFAULT;
    }
    else if (lng != _T("default"))
    {
        const wxLanguageInfo *info = wxLocale::FindLanguageInfo(lng);
        if (info != NULL)
            lang = (wxLanguage)info->Language;
        else
            wxLogError(_("Uknown locale code '%s' in registry."), lng.c_str());
    }
    return lang;
#endif // NEED_CHOOSELANG_UI
}

#if NEED_CHOOSELANG_UI
wxLanguage ChooseLanguage()
{
    struct LangInfo
    {
        wxString name;
        wxLanguage code;
    };

	LangInfo langs[] =
    {
        { _("(Use default language)"), wxLANGUAGE_DEFAULT },

        { _("Croatian"), wxLANGUAGE_CROATIAN },
        { _("Czech"), wxLANGUAGE_CZECH },
        { _("Dutch"), wxLANGUAGE_DUTCH },
        { _("English"), wxLANGUAGE_ENGLISH },
        { _("French"), wxLANGUAGE_FRENCH },
        { _("German"), wxLANGUAGE_GERMAN },
        { _("Italian"), wxLANGUAGE_ITALIAN },
        { _("Polish"), wxLANGUAGE_POLISH },
        { _("Portuguese"), wxLANGUAGE_PORTUGUESE },
        { _("Russian"), wxLANGUAGE_RUSSIAN },
        { _("Spanish"), wxLANGUAGE_SPANISH },
        { _("Ukrainian"), wxLANGUAGE_UKRAINIAN },
        { _T(""), wxLANGUAGE_UNKNOWN }
    };

    wxArrayString arr;
    for (int i = 0; !langs[i].name.empty(); i++)
        arr.Add(langs[i].name);

    int choice = wxGetSingleChoiceIndex(
            _("Select your preferred language"),
            _("Language selection"),
            arr);
    if (choice == -1)
        return wxLANGUAGE_UNKNOWN;
    else
        return langs[choice].code;
}

void ChangeUILanguage()
{
    wxLanguage lang = ChooseLanguage();
    if (lang == wxLANGUAGE_UNKNOWN)
        return;
    SaveUILanguage(lang);
	CUtils::MsgInfo( _("You must restart the program for this change to take effect.") );
}

#endif // NEED_CHOOSELANG_UI
