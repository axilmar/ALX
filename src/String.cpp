#include "String.hpp"


namespace alx {


///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////


//constructor from wide character.
String::String(wchar_t ch) {
    char s[5];
    size_t sz = al_utf8_encode(s, ch);
    s[sz] = '\0';
    printf("%s", s);
}


//Removes the first occurrence of the given code point.
int String::findAndRemove(int32_t cp, int offset /*= 0*/) {
    return _findAndExecute(cp, offset, [](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_chr(str, ofs) ? ofs : -1;
    });
}


//Removes the first occurrence of the given string.
int String::findAndRemove(const ALLEGRO_USTR *str, int offset /*= 0*/) {
    int sz = al_ustr_size(str);
    return _findAndExecute(str, offset, [=](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_range(str, ofs, ofs + sz) ? ofs : -1;
    });
}


//Removes all code points that match the given code point.
int String::findAndRemoveAll(int32_t cp, int offset /*= 0*/) {
    return _findAndExecuteAll(cp, offset, [](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_chr(str, ofs) ? ofs : -1;
    });
}


//Removes all strings that match the given string.
int String::findAndRemoveAll(const ALLEGRO_USTR *str, int offset /*= 0*/) {
    int sz = al_ustr_size(str);
    return _findAndExecuteAll(str, offset, [=](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_range(str, ofs, ofs + sz) ? ofs : -1;
    });
}


//Removes the last occurence of the given code point.
int String::findReverseAndRemove(int32_t cp, int offset /*= -1*/) {
    return _findReverseAndExecute(cp, offset, [](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_chr(str, ofs) ? ofs : -1;
    });
}


//Removes the last occurence of the given string.
int String::findReverseAndRemove(const ALLEGRO_USTR *str, int offset /*= -1*/) {
    int sz = al_ustr_size(str);
    return _findReverseAndExecute(str, offset, [=](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_range(str, ofs, ofs + sz) ? ofs : -1;
    });
}


//Removes all code points that match the given code point.
int String::findReverseAndRemoveAll(int32_t cp, int offset /*= -1*/) {
    return _findReverseAndExecuteAll(cp, offset, [](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_chr(str, ofs) ? ofs : -1;
    });
}


//Removes all strings that match the given string.
int String::findReverseAndRemoveAll(const ALLEGRO_USTR *str, int offset /*= -1*/) {
    int sz = al_ustr_size(str);
    return _findReverseAndExecuteAll(str, offset, [=](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_remove_range(str, ofs, ofs + sz) ? ofs : -1;
    });
}


//Searches for a code point and replaces it with a new one.
int String::findAndReplace(int32_t oldCP, int32_t newCP, int offset /*= 0*/) {
    return _findAndExecute(oldCP, offset, [=](ALLEGRO_USTR *str, int ofs) {
        size_t sz = al_ustr_set_chr(str, ofs, newCP);
        return sz > 0 ? (int)sz : -1;
    });
}


//Searches for a string and replaces it with a new one.
int String::findAndReplace(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset /*= 0*/) {
    return _findAndExecute(oldStr, offset, [=](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_replace_range(str, ofs, ofs + al_ustr_size(oldStr), newStr) ? ofs + al_ustr_size(newStr) : -1;
    });
}


//Replaces all code points that match the given one.
int String::findAndReplaceAll(int32_t oldCP, int32_t newCP, int offset /*= 0*/) {
    return _findAndExecuteAll(oldCP, offset, [=](ALLEGRO_USTR *str, int ofs) {
        size_t sz = al_ustr_set_chr(str, ofs, newCP);
        return sz > 0 ? (int)sz : -1;
    });
}


//Replaces all strings that match the given one.
int String::findAndReplaceAll(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset /*= 0*/) {
    return _findAndExecuteAll(oldStr, offset, [=](ALLEGRO_USTR *str, int ofs) {
        return al_ustr_replace_range(str, ofs, ofs + al_ustr_size(oldStr), newStr) ? ofs + al_ustr_size(newStr) : -1;
    });
}


//Searches for a code point and replaces it with a new one.
int String::findReverseAndReplace(int32_t oldCP, int32_t newCP, int offset /*= -1*/) {
    return _findReverseAndExecute(oldCP, offset, [=](ALLEGRO_USTR *str, int ofs) {
        int sz = (int)al_ustr_set_chr(str, ofs, newCP);
        if (!sz) return -1;
        al_ustr_prev(str, &sz);
        return sz;
    });
}


//Searches for a string and replaces it with a new one.
int String::findReverseAndReplace(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset /*= -1*/) {
    return _findReverseAndExecute(oldStr, offset, [=](ALLEGRO_USTR *str, int ofs) {
        if (!al_ustr_replace_range(str, ofs, ofs + al_ustr_size(oldStr), newStr)) return -1;
        al_ustr_prev(str, &ofs);
        return ofs;
    });
}


//Replaces all code points that match the given one, searching in reverse order.
int String::findReverseAndReplaceAll(int32_t oldCP, int32_t newCP, int offset /*= -1*/) {
    return _findReverseAndExecuteAll(oldCP, offset, [=](ALLEGRO_USTR *str, int ofs) {
        int sz = (int)al_ustr_set_chr(str, ofs, newCP);
        if (!sz) return -1;
        al_ustr_prev(str, &sz);
        return sz;
    });
}


//Replaces all strings that match the given one, searching in reverse order.
int String::findReverseAndReplaceAll(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset /*= -1*/) {
    return _findReverseAndExecuteAll(oldStr, offset, [=](ALLEGRO_USTR *str, int ofs) {
        if (!al_ustr_replace_range(str, ofs, ofs + al_ustr_size(oldStr), newStr)) return -1;
        al_ustr_prev(str, &ofs);
        return ofs;
    });
}



///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////


//converts wide character string to UTF8.
std::string String::_wideCharToUTF8(const wchar_t *str) {
    std::string result;
    for(; *str; ++str) {
        char s[5];
        size_t sz = al_utf8_encode(s, *str);
        s[sz] = '\0';
        result += s;
    }
    return result;
}


} //namespace alx
