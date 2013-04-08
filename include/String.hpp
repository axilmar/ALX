#ifndef ALX_STRING_HPP
#define ALX_STRING_HPP


#include <cstring>
#include <string>
#include <sstream>
#include <stdexcept>
#include <allegro5/allegro.h>
#include "Shared.hpp"
#include "Char.hpp"


namespace alx {


/**
    Shared-based wrapper class around ALLEGRO_USTR.
 */
class String : public Shared<ALLEGRO_USTR> {
public:
    /*=========================================================================
     * CONSTRUCTORS.        
     *=========================================================================*/

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    String(ALLEGRO_USTR *object, bool managed = true) : 
        Shared(object, managed, al_ustr_free, [](ALLEGRO_USTR *){})
    {
    }

    /**
        null string constructor.
     */
    String() {
    }

    /**
        Constructor from character.
        Use the special class Char to represent a character
        because 'char' in C has dual meaning.
     */
    String(Char c) {
        printf("%c", c.get());
    }

    /**
        constructor from wide character.
        @param ch character.
     */
    String(wchar_t ch);

    /**
        constructor from null-terminated string.
        @param str string.
     */
    String(const char *str) : 
        Shared(al_ustr_new(str), al_ustr_free)
    {
    }

    /**
        constructor from null-terminated wide character string.
        The string is converted to UTF8.
        @param str string.
     */
    String(const wchar_t *str) : 
        Shared(al_ustr_new(_wideCharToUTF8(str).c_str()), al_ustr_free)
    {
    }

    /**
        Constructor from 8-bit integer.
        @param v value.
     */
    String(int8_t v) {
        printf("%i", (int)v);
    }

    /**
        Constructor from 16-bit integer.
        @param v value.
     */
    String(int16_t v) {
        printf("%i", (int)v);
    }

    /**
        Constructor from 32-bit integer.
        @param v value.
     */
    String(int32_t v) {
        printf("%i", v);
    }

    /**
        Constructor from 64-bit integer.
        @param v value.
     */
    String(int64_t v) {
        printf("%lli", v);
    }

    /**
        Constructor from 8-bit unsigned integer.
        @param v value.
     */
    String(uint8_t v) {
        printf("%i", v);
    }

    /**
        Constructor from 16-bit unsigned integer.
        @param v value.
     */
    String(uint16_t v) {
        printf("%u", (int)v);
    }

    /**
        Constructor from 32-bit unsigned integer.
        @param v value.
     */
    String(uint32_t v) {
        printf("%u", v);
    }

    /**
        Constructor from 64-bit unsigned integer.
        @param v value.
     */
    String(uint64_t v) {
        printf("%llu", v);
    }

    /**
        Constructor from float.
        @param v value.
     */
    String(float v) {
        printf("%f", (double)v);
    }

    /**
        Constructor from double.
        @param v value.
     */
    String(double v) {
        printf("%f", v);
    }

    /**
        Constructor from long double.
        @param v value.
     */
    String(long double v) {
        printf("%Lf", v);
    }

    /**
        Constructor from boolean.
        @param v value.
     */
    String(bool b) {
        printf("%s", b ? "true" : "false");
    }

    /**
        Constructor from pointer.
        @param v pointer value.
     */
    String(void *v) {
        printf("%p", v);
    }

    /**
        Constructor from std::string.
        @param str string.
     */
    String(const std::string &str) : 
        Shared(al_ustr_new(str.c_str()), al_ustr_free)
    {
    }

    /**
        Constructor from std::wstring.
        @param str string.
     */
    String(const std::wstring &str) : 
        Shared(al_ustr_new(_wideCharToUTF8(str.c_str()).c_str()), al_ustr_free)
    {
    }

    /**
        Constructor from substring.
        @param str source string.
        @param startOffset start offset into source.
        @param endOffset end offset into source.
     */
    String(const String &str, int startOffset, int endOffset) : 
        Shared(al_ustr_dup_substr(str.get(), startOffset, endOffset), al_ustr_free)
    {
    }

    /**
        Constructor from substring.
        @param str source string.
        @param startOffset start offset into source.
        @param endOffset end offset into source.
     */
    String(ALLEGRO_USTR *str, int startOffset, int endOffset) : 
        Shared(al_ustr_dup_substr(str, startOffset, endOffset), al_ustr_free)
    {
    }

    /**
        Constructor from substring.
        @param str source string.
        @param startOffset start offset into source.
        @param endOffset end offset into source.
     */
    String(const char *str, int startOffset, int endOffset, ALLEGRO_USTR_INFO info = ALLEGRO_USTR_INFO()) : 
        Shared(al_ustr_dup_substr(al_ref_cstr(&info, str), startOffset, endOffset), al_ustr_free)
    {
    }

    /**
        The copy constructor.
        @param str source object.
     */
    String(const String &str) : Shared(str) {
    }

    /**
        The move constructor.
        @param str source object.
     */
    String(String &&str) : Shared(str) {
    }

    /*=========================================================================
     * CONVERSIONS.        
     *=========================================================================*/

    /**
        Conversion to character.
        @return the first character.
     */
    operator Char () const {
        return al_ustr_get(get(), 0);
    }

    /**
        Conversion to null-terminated string.
        @return null-terminated string.
     */
    operator const char *() const {
        al_cstr(get());
    }

    /**
        conversion to int8_t.
        @return the converted value.
     */
    operator int8_t () const {
        return (int8_t)_convert<int16_t>();
    }

    /**
        conversion to int16_t.
        @return the converted value.
     */
    operator int16_t () const {
        return _convert<int16_t>();
    }

    /**
        conversion to int32_t.
        @return the converted value.
     */
    operator int32_t () const {
        return _convert<int32_t>();
    }

    /**
        conversion to int64_t.
        @return the converted value.
     */
    operator int64_t () const {
        return _convert<int64_t>();
    }

    /**
        conversion to uint8_t.
        @return the converted value.
     */
    operator uint8_t () const {
        return _convert<uint16_t>();
    }

    /**
        conversion to uint16_t.
        @return the converted value.
     */
    operator uint16_t () const {
        return _convert<uint16_t>();
    }

    /**
        conversion to uint32_t.
        @return the converted value.
     */
    operator uint32_t () const {
        return _convert<uint32_t>();
    }

    /**
        conversion to uint64_t.
        @return the converted value.
     */
    operator uint64_t () const {
        return _convert<uint64_t>();
    }

    /**
        conversion to float.
        @return the converted value.
     */
    operator float () const {
        return _convert<float>();
    }

    /**
        conversion to double.
        @return the converted value.
     */
    operator double () const {
        return _convert<double>();
    }

    /**
        conversion to long double.
        @return the converted value.
     */
    operator long double () const {
        return _convert<long double>();
    }

    /**
        conversion to boolean.
        @return true, if the string equals 'true', false otherwise.
     */
    operator bool () const {
        return operator == ("true");
    }

    /**
        Conversion to std::wstring.
        @return the std string.
     */
    operator std::wstring () const {
        return _convert<std::wstring>();
    }

    /*=========================================================================
     * COMPARISONS.        
     *=========================================================================*/

     /**
        Checks if this and given string are equal.
        @param str string.
        @return true on success.
      */
     bool operator == (const String &str) const {
        return al_ustr_equal(get(), str.get());
     }

     /**
        Checks if this and given string are equal.
        @param str string.
        @return true on success.
      */
     bool operator == (const ALLEGRO_USTR *str) const {
        return al_ustr_equal(get(), str);
     }

     /**
        Checks if this and given string are equal.
        @param str string.
        @return true on success.
      */
     bool operator == (const char *str) const {
        ALLEGRO_USTR_INFO info;
        return al_ustr_equal(get(), al_ref_cstr(&info, str));
     }

     /**
        Checks if this and given string are different.
        @param str string.
        @return true on success.
      */
     bool operator != (const String &str) const {
        return !operator == (str);
     }

     /**
        Checks if this and given string are different.
        @param str string.
        @return true on success.
      */
     bool operator != (const ALLEGRO_USTR *str) const {
        return !operator == (str);
     }

     /**
        Checks if this and given string are different.
        @param str string.
        @return true on success.
      */
     bool operator != (const char *str) const {
        return !operator == (str);
     }

     /**
        Checks if this comes before the given string in sorting.
        @param str string.
        @return true on success.
      */
     bool operator < (const String &str) const {
        return al_ustr_compare(get(), str.get()) < 0;
     }

     /**
        Checks if this comes before the given string in sorting.
        @param str string.
        @return true on success.
      */
     bool operator < (const ALLEGRO_USTR *str) const {
        return al_ustr_compare(get(), str) < 0;
     }

     /**
        Checks if this comes before the given string in sorting.
        @param str string.
        @return true on success.
      */
     bool operator < (const char *str) const {
        ALLEGRO_USTR_INFO info;
        return al_ustr_compare(get(), al_ref_cstr(&info, str)) < 0;
     }

     /**
        Checks if this comes before the given string in sorting or if the strings are equal.
        @param str string.
        @return true on success.
      */
     bool operator <= (const String &str) const {
        return al_ustr_compare(get(), str.get()) <= 0;
     }

     /**
        Checks if this comes before the given string in sorting or if the strings are equal.
        @param str string.
        @return true on success.
      */
     bool operator <= (const ALLEGRO_USTR *str) const {
        return al_ustr_compare(get(), str) <= 0;
     }

     /**
        Checks if this comes before the given string in sorting or if the strings are equal.
        @param str string.
        @return true on success.
      */
     bool operator <= (const char *str) const {
        ALLEGRO_USTR_INFO info;
        return al_ustr_compare(get(), al_ref_cstr(&info, str)) <= 0;
     }

     /**
        Checks if this comes after the given string in sorting.
        @param str string.
        @return true on success.
      */
     bool operator > (const ALLEGRO_USTR *str) const {
        return al_ustr_compare(get(), str) > 0;
     }

     /**
        Checks if this comes after the given string in sorting.
        @param str string.
        @return true on success.
      */
     bool operator > (const char *str) const {
        ALLEGRO_USTR_INFO info;
        return al_ustr_compare(get(), al_ref_cstr(&info, str)) > 0;
     }

     /**
        Checks if this comes after the given string in sorting or if the strings are equal.
        @param str string.
        @return true on success.
      */
     bool operator >= (const String &str) const {
        return al_ustr_compare(get(), str.get()) >= 0;
     }

     /**
        Checks if this comes after the given string in sorting or if the strings are equal.
        @param str string.
        @return true on success.
      */
     bool operator >= (const ALLEGRO_USTR *str) const {
        return al_ustr_compare(get(), str) >= 0;
     }

     /**
        Checks if this comes after the given string in sorting or if the strings are equal.
        @param str string.
        @return true on success.
      */
     bool operator >= (const char *str) const {
        ALLEGRO_USTR_INFO info;
        return al_ustr_compare(get(), al_ref_cstr(&info, str)) >= 0;
     }

    /*=========================================================================
     * FIND. 
     *=========================================================================*/

     /**
        Locates the offset of the first instance of the given code point.
        @param cp code point to find.
        @param startOffset offset to start the search from.
        @return the offset it is found or -1 if it is not found.
      */
     int find(int cp, int startOffset = 0) const {
        return al_ustr_find_chr(get(), startOffset, cp);
     }

     /**
        Locates the offset of the first instance of the given string.
        @param str string to find.
        @param startOffset offset to start the search from.
        @return the offset it is found or -1 if it is not found.
      */
     int find(const String &str, int startOffset = 0) const {
        return al_ustr_find_str(get(), startOffset, str.get());
     }

     /**
        Locates the offset of the first instance of the given string.
        @param str string to find.
        @param startOffset offset to start the search from.
        @return the offset it is found or -1 if it is not found.
      */
     int find(const ALLEGRO_USTR *str, int startOffset = 0) const {
        return al_ustr_find_str(get(), startOffset, str);
     }

     /**
        Locates the offset of the first instance of the given string.
        @param str string to find.
        @param startOffset offset to start the search from.
        @return the offset it is found or -1 if it is not found.
      */
     int find(const char *str, int startOffset = 0) const {
        return al_ustr_find_cstr(get(), startOffset, str);
     }

     /**
        Locates the offset of the first instance of the given code point.
        @param cp code point to find.
        @param offset offset to start the search from; if -1, the search start from the end of the string.
        @return the offset it is found or -1 if it is not found.
      */
     int findReverse(int cp, int offset = -1) const {
        return al_ustr_find_chr(get(), _getReverseOffset(offset), cp);
     }

     /**
        Locates the offset of the first instance of the given string.
        @param str string to find.
        @param offset offset to start the search from; if -1, the search start from the end of the string.
        @return the offset it is found or -1 if it is not found.
      */
     int findReverse(const String &str, int offset = -1) const {
        return al_ustr_rfind_str(get(), _getReverseOffset(offset), str.get());
     }

     /**
        Locates the offset of the first instance of the given string.
        @param str string to find.
        @param offset offset to start the search from; if -1, the search start from the end of the string.
        @return the offset it is found or -1 if it is not found.
      */
     int findReverse(const ALLEGRO_USTR *str, int offset = -1) const {
        return al_ustr_rfind_str(get(), _getReverseOffset(offset), str);
     }

     /**
        Locates the offset of the first instance of the given string.
        @param str string to find.
        @param offset offset to start the search from; if -1, the search start from the end of the string.
        @return the offset it is found or -1 if it is not found.
      */
     int findReverse(const char *str, int offset = -1) const {
        return al_ustr_rfind_cstr(get(), _getReverseOffset(offset), str);
     }

     /**
        Locates the offset of the first instance of a character in the given set.
        @param set string with characters to find.
        @param startOffset offset to start the search from.
        @return the offset it is found or -1 if it is not found.
      */
     int findSet(const String &set, int startOffset = 0) const {
        return al_ustr_find_set(get(), startOffset, set.get());
     }

     /**
        Locates the offset of the first instance of the given string.
        @param set string with characters to find.
        @param startOffset offset to start the search from.
        @return the offset it is found or -1 if it is not found.
      */
     int findSet(const ALLEGRO_USTR *set, int startOffset = 0) const {
        return al_ustr_find_set(get(), startOffset, set);
     }

     /**
        Locates the offset of the first instance of the given string.
        @param set string with characters to find.
        @param startOffset offset to start the search from.
        @return the offset it is found or -1 if it is not found.
      */
     int findSet(const char *set, int startOffset = 0) const {
        return al_ustr_find_set_cstr(get(), startOffset, set);
     }

     /**
        Locates the offset of the first instance of a character not in the given set.
        @param set string with characters to find.
        @param startOffset offset to start the search from.
        @return the offset it is not found or -1 if it is found.
      */
     int findSetInverse(const String &set, int startOffset = 0) const {
        return al_ustr_find_set(get(), startOffset, set.get());
     }

     /**
        Locates the offset of the first instance of the given string.
        @param set string with characters to find.
        @param startOffset offset to start the search from.
        @return the offset it is not found or -1 if it is found.
      */
     int findSetInverse(const ALLEGRO_USTR *set, int startOffset = 0) const {
        return al_ustr_find_set(get(), startOffset, set);
     }

     /**
        Locates the offset of the first instance of the given string.
        @param set string with characters to find.
        @param startOffset offset to start the search from.
        @return the offset it is not found or -1 if it is found.
      */
     int findSetInverse(const char *set, int startOffset = 0) const {
        return al_ustr_find_set_cstr(get(), startOffset, set);
     }

     /**
        Checks if this string starts with the given code point.
        @param cp code point.
        @return true on success.
      */
     bool startsWith(int cp) const {
        return startsWith(String(Char(cp)));
     }

     /**
        Checks if this string starts with the given string.
        @param str string.
        @return true on success.
      */
     bool startsWith(const String &str) const {
        return al_ustr_has_prefix(get(), str.get());
     }

     /**
        Checks if this string starts with the given string.
        @param str string.
        @return true on success.
      */
     bool startsWith(const ALLEGRO_USTR *str) const {
        return al_ustr_has_prefix(get(), str);
     }

     /**
        Checks if this string starts with the given string.
        @param str string.
        @return true on success.
      */
     bool startsWith(const char *str) const {
        return al_ustr_has_prefix_cstr(get(), str);
     }

     /**
        Checks if this string ends with the given code point.
        @param cp code point.
        @return true on success.
      */
     bool endsWith(int cp) const {
        return endsWith(String(Char(cp)));
     }

     /**
        Checks if this string ends with the given string.
        @param str string.
        @return true on success.
      */
     bool endsWith(const String &str) const {
        return al_ustr_has_suffix(get(), str.get());
     }

     /**
        Checks if this string ends with the given string.
        @param str string.
        @return true on success.
      */
     bool endsWith(const ALLEGRO_USTR *str) const {
        return al_ustr_has_suffix(get(), str);
     }

     /**
        Checks if this string ends with the given string.
        @param str string.
        @return true on success.
      */
     bool endsWith(const char *str) const {
        return al_ustr_has_suffix_cstr(get(), str);
     }

    /*=========================================================================
     * ACCESSORS. 
     *=========================================================================*/

     /**
        Returns the string size, in bytes.
        @return the string size, in bytes.
      */
     size_t getSize() const {
        return al_ustr_size(get());
     }

     /**
        Checks if the string is empty.
        @return true if empty.
      */
     bool isEmpty() const {
        return al_ustr_equal(get(), al_ustr_empty_string());
     }

     /**
        Returns the string code point count.
        @return the string code point count.
      */
     size_t getLength() const {
        return al_ustr_length(get());
     }

     /**
        Returns the byte offset of the given code point.
        @param index index of code point.
        @return the byte offset of the code point at the given index.
      */
     int getOffset(int codePointIndex) const {
        return al_ustr_offset(get(), codePointIndex);
     }

     /**
        Returns the code point at the specified byte offset.
        @return the code point at the specified byte offset.
      */
     int32_t getCodePoint(int offset) const {
        return al_ustr_get(get(), offset);
     }

    /*=========================================================================
     * INSERT. 
     *=========================================================================*/

     /**
        Inserts the given code point at the beginning of the string.
        @param cp code point to insert.
        @return true on success.
      */
     bool prepend(int32_t cp) {
        return al_ustr_insert_chr(get(), 0, cp) > 0;
     }

     /**
        Inserts the given string at the beginning of the string.
        @param string string to insert.
        @return true on success.
      */
     bool prepend(const String &str) {
        return al_ustr_insert(get(), 0, str.get());
     }

     /**
        Inserts the given string at the beginning of the string.
        @param string string to insert.
        @return true on success.
      */
     bool prepend(const ALLEGRO_USTR *str) {
        return al_ustr_insert(get(), 0, str);
     }

     /**
        Inserts the given string at the beginning of the string.
        @param string string to insert.
        @return true on success.
      */
     bool prepend(const char *str) {
        return al_ustr_insert_cstr(get(), 0, str);
     }

     /**
        Inserts the given code point at the given position.
        @param cp code point to insert.
        @param offset byte offset to insert the code point at.
        @return true on success.
      */
     bool insert(int32_t cp, int offset) {
        return al_ustr_insert_chr(get(), offset, cp);
     }

     /**
        Inserts the given string at the given position.
        @param str string to insert.
        @param offset byte offset to insert the string at.
        @return true on success.
      */
     bool insert(const String &str, int offset) {
        return al_ustr_insert(get(), offset, str.get());
     }

     /**
        Inserts the given string at the given position.
        @param str string to insert.
        @param offset byte offset to insert the string at.
        @return true on success.
      */
     bool insert(const ALLEGRO_USTR *str, int offset) {
        return al_ustr_insert(get(), offset, str);
     }

     /**
        Inserts the given string at the given position.
        @param str string to insert.
        @param offset byte offset to insert the string at.
        @return true on success.
      */
     bool insert(const char *str, int offset) {
        return al_ustr_insert_cstr(get(), offset, str);
     }

     /**
        Inserts the given code point at the end of the string.
        @param cp code point to insert.
        @return true on success.
      */
     bool append(int32_t cp) {
        return al_ustr_append_chr(get(), cp) > 0;
     }

     /**
        Inserts the given string at the end of the string.
        @param string string to insert.
        @return true on success.
      */
     bool append(const String &str) {
        return al_ustr_append(get(), str.get());
     }

     /**
        Inserts the given string at the end of the string.
        @param string string to insert.
        @return true on success.
      */
     bool append(const ALLEGRO_USTR *str) {
        return al_ustr_append(get(), str);
     }

     /**
        Inserts the given string at the end of the string.
        @param string string to insert.
        @return true on success.
      */
     bool append(const char *str) {
        return al_ustr_append_cstr(get(), str);
     }

    /*=========================================================================
     * REMOVE. 
     *=========================================================================*/

     /**
        Removes a single character at the given offset.
        @param offset byte offset.
        @return true on success.
      */
     bool remove(int offset) {
        return al_ustr_remove_chr(get(), offset);
     }

     /**
        Removes characters in a range.
        @param startOffset start offset.
        @param endOffset end offset.
        @return true on success.
      */
    bool remove(int startOffset, int endOffset) {
        return al_ustr_remove_range(get(), startOffset, endOffset);
    }

    /**
        Removes the first occurrence of the given code point.
        @param cp code point.
        @param offset start offset.
        @return offset of removed code point or -1 if not found.
     */
    int findAndRemove(int32_t cp, int offset = 0);

    /**
        Removes the first occurrence of the given string.
        @param string string.
        @param offset start offset.
        @return offset of removed string or -1 if not found.
     */
    int findAndRemove(const ALLEGRO_USTR *str, int offset = 0);

    /**
        Removes the first occurrence of the given string.
        @param string string.
        @param offset start offset.
        @return offset of removed string or -1 if not found.
     */
    int findAndRemove(const String &str, int offset = 0) {
        return findAndRemove(str.get(), offset);
    }

    /**
        Removes the first occurrence of the given string.
        @param string string.
        @param offset start offset.
        @return offset of removed string or -1 if not found.
     */
    int findAndRemove(const char *str, int offset = 0) {
        ALLEGRO_USTR_INFO info;
        return findAndRemove(al_ref_cstr(&info, str), offset);
    }

    /**
        Removes all code points that match the given code point.
        @param cp code point to find.
        @param offset start offset.
        @return offset of last code point found or -1 if none is found.
     */
    int findAndRemoveAll(int32_t cp, int offset = 0);

    /**
        Removes all strings that match the given string.
        @param str string to find.
        @param offset start offset.
        @return offset of last string found or -1 if none is found.
     */
    int findAndRemoveAll(const ALLEGRO_USTR *str, int offset = 0);

    /**
        Removes all strings that match the given string.
        @param str string to find.
        @param offset start offset.
        @return offset of last string found or -1 if none is found.
     */
    int findAndRemoveAll(const String &str, int offset = 0) {
        return findAndRemoveAll(str.get(), offset);
    }

    /**
        Removes all strings that match the given string.
        @param str string to find.
        @param offset start offset.
        @return offset of last string found or -1 if none is found.
     */
    int findAndRemoveAll(const char *str, int offset = 0) {
        ALLEGRO_USTR_INFO info;
        return findAndRemove(al_ref_cstr(&info, str), offset);
    }

    /**
        Removes the last occurence of the given code point.
        @param cp code point.
        @param offset start offset.
        @return offset of removed code point or -1 if not found.
     */
    int findReverseAndRemove(int32_t cp, int offset = -1);

    /**
        Removes the last occurence of the given string.
        @param string string.
        @param offset start offset.
        @return offset of removed string or -1 if not found.
     */
    int findReverseAndRemove(const ALLEGRO_USTR *str, int offset = -1);

    /**
        Removes the last occurence of the given string.
        @param string string.
        @param offset start offset.
        @return offset of removed string or -1 if not found.
     */
    int findReverseAndRemove(const String &str, int offset = -1) {
        return findReverseAndRemove(str.get(), offset);
    }

    /**
        Removes the last occurence of the given string.
        @param string string.
        @param offset start offset.
        @return offset of removed string or -1 if not found.
     */
    int findReverseAndRemove(const char *str, int offset = -1) {
        ALLEGRO_USTR_INFO info;
        return findReverseAndRemove(al_ref_cstr(&info, str), offset);
    }

    /**
        Removes all code points that match the given code point.
        @param cp code point to find.
        @param offset start offset.
        @return offset of last code point found or -1 if none is found.
     */
    int findReverseAndRemoveAll(int32_t cp, int offset = -1);

    /**
        Removes all strings that match the given string.
        @param str string to find.
        @param offset start offset.
        @return offset of last string found or -1 if none is found.
     */
    int findReverseAndRemoveAll(const ALLEGRO_USTR *str, int offset = -1);

    /**
        Removes all strings that match the given string.
        @param str string to find.
        @param offset start offset.
        @return offset of last string found or -1 if none is found.
     */
    int findReverseAndRemoveAll(const String &str, int offset = -1) {
        return findReverseAndRemoveAll(str.get(), offset);
    }

    /**
        Removes all strings that match the given string.
        @param str string to find.
        @param offset start offset.
        @return offset of last string found or -1 if none is found.
     */
    int findReverseAndRemoveAll(const char *str, int offset = -1) {
        ALLEGRO_USTR_INFO info;
        return findReverseAndRemoveAll(al_ref_cstr(&info, str), offset);
    }

    /*=========================================================================
     * REPLACE. 
     *=========================================================================*/

     /**
        Replaces the code point at the given offset by the given code point.
        @param offset offset to replace at.
        @param cp new code point.
        @return offset to the following code point.
      */
     int replace(int offset, int32_t cp) {
        size_t r = al_ustr_set_chr(get(), offset, cp);
        return r > 0 ? (int)r : -1;
     }

     /**
        Replaces a range of code points with the given string.
        @param str string.
        @return offset to the code point following the string or -1 if the operation failed.
      */
     int replace(int startOffset, int endOffset, const String &str) {
        return al_ustr_replace_range(get(), startOffset, endOffset, str.get()) ? startOffset + str.getSize() : -1;
     }

     /**
        Replaces a range of code points with the given string.
        @param str string.
        @return offset to the code point following the string or -1 if the operation failed.
      */
     int replace(int startOffset, int endOffset, const ALLEGRO_USTR *str) {
        return al_ustr_replace_range(get(), startOffset, endOffset, str) ? startOffset + al_ustr_size(str) : -1;
     }

     /**
        Replaces a range of code points with the given string.
        @param str string.
        @return offset to the code point following the string or -1 if the operation failed.
      */
     int replace(int startOffset, int endOffset, const char *str) {
        ALLEGRO_USTR_INFO info;
        const ALLEGRO_USTR *ustr = al_ref_cstr(&info, str);
        return al_ustr_replace_range(get(), startOffset, endOffset, ustr) ? startOffset + al_ustr_size(ustr) : -1;
     }

     /**
        Searches for a code point and replaces it with a new one.
        @param oldCP code point to find.
        @param newCP new code point.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplace(int32_t oldCP, int32_t newCP, int offset = 0);

     /**
        Searches for a string and replaces it with a new one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplace(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset = 0);

     /**
        Searches for a string and replaces it with a new one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplace(const String &oldStr, const String &newStr, int offset = 0) {
        return findAndReplace(oldStr.get(), newStr.get(), offset);
     }

     /**
        Searches for a string and replaces it with a new one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplace(const char *oldStr, const char *newStr, int offset = 0) {
        ALLEGRO_USTR_INFO oldInfo, newInfo;
        return findAndReplace(al_ref_cstr(&oldInfo, oldStr), al_ref_cstr(&newInfo, newStr), offset);
     }

     /**
        Replaces all code points that match the given one.
        @param oldCP code point to find.
        @param newCP new code point.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplaceAll(int32_t oldCP, int32_t newCP, int offset = 0);

     /**
        Replaces all strings that match the given one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplaceAll(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset = 0);

     /**
        Replaces all strings that match the given one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplaceAll(const String &oldStr, const String &newStr, int offset = 0) {
        return findAndReplaceAll(oldStr.get(), newStr.get(), offset);
     }

     /**
        Replaces all strings that match the given one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findAndReplaceAll(const char *oldStr, const char *newStr, int offset = 0) {
        ALLEGRO_USTR_INFO oldInfo, newInfo;
        return findAndReplaceAll(al_ref_cstr(&oldInfo, oldStr), al_ref_cstr(&newInfo, newStr), offset);
     }

     /**
        Searches for a code point and replaces it with a new one.
        @param oldCP code point to find.
        @param newCP new code point.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplace(int32_t oldCP, int32_t newCP, int offset = -1);

     /**
        Searches for a string and replaces it with a new one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplace(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset = -1);

     /**
        Searches for a string and replaces it with a new one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplace(const String &oldStr, const String &newStr, int offset = -1) {
        return findReverseAndReplace(oldStr.get(), newStr.get(), offset);
     }

     /**
        Searches for a string and replaces it with a new one.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplace(const char *oldStr, const char *newStr, int offset = -1) {
        ALLEGRO_USTR_INFO oldInfo, newInfo;
        return findReverseAndReplace(al_ref_cstr(&oldInfo, oldStr), al_ref_cstr(&newInfo, newStr), offset);
     }

     /**
        Replaces all code points that match the given one, searching in reverse order.
        @param oldCP code point to find.
        @param newCP new code point.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplaceAll(int32_t oldCP, int32_t newCP, int offset = -1);

     /**
        Replaces all strings that match the given one, searching in reverse order.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplaceAll(const ALLEGRO_USTR *oldStr, const ALLEGRO_USTR *newStr, int offset = -1);

     /**
        Replaces all strings that match the given one, searching in reverse order.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplaceAll(const String &oldStr, const String &newStr, int offset = -1) {
        return findReverseAndReplaceAll(oldStr.get(), newStr.get(), offset);
     }

     /**
        Replaces all strings that match the given one, searching in reverse order.
        @param oldStr old string.
        @param newStr new string.
        @param offset offset to start the search from.
        @return offset of next code point or -1 if not found.
      */
     int findReverseAndReplaceAll(const char *oldStr, const char *newStr, int offset = -1) {
        ALLEGRO_USTR_INFO oldInfo, newInfo;
        return findReverseAndReplaceAll(al_ref_cstr(&oldInfo, oldStr), al_ref_cstr(&newInfo, newStr), offset);
     }

private:
    //converts the string to UTF8 character sequence
    static std::string _wideCharToUTF8(const wchar_t *str);

    //convert to given type
    template <class T> T _convert() const {
        std::wstringstream stream;
        stream << (const char *)(*this);
        T result;
        stream >> result;
        return result;
    }

    //get reverse offset
    int _getReverseOffset(int offset) const {
        return offset >= 0 ? offset : al_ustr_size(get());
    }

    //find item and execute function on it
    template <class T, class F> int _findAndExecute(T&& t, int offset, F f) {
        offset = find(t, offset);
        return offset >= 0 ? f(get(), offset) : -1;
    }

    //find all items and execute function on it
    template <class T, class F> int _findAndExecuteAll(T&& t, int offset, F f) {
        int result = -1;
        for(offset = find(t, offset); offset != -1; offset = find(t, offset)) {
            result = f(get(), offset);
        }
        return result;
    }

    //find item in reverse and execute function on it
    template <class T, class F> int _findReverseAndExecute(T&& t, int offset, F f) {
        offset = findReverse(t, _getReverseOffset(offset));
        return offset >= 0 ? f(get(), offset) : -1;
    }

    //find all items in reverse and execute function on it
    template <class T, class F> int _findReverseAndExecuteAll(T&& t, int offset, F f) {
        int result = -1;
        for(offset = findReverse(t, _getReverseOffset(offset)); offset != -1; offset = findReverse(t, offset)) {
            result = f(get(), offset);
        }
        return result;
    }
};


} //namespace alx


#endif //ALX_STRING_HPP
