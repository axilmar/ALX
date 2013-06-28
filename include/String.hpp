#ifndef ALX_STRING_HPP
#define ALX_STRING_HPP


#include <climits>
#include <string>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <allegro5/allegro.h>
#include "Shared.hpp"
#include "Fixed.hpp"


namespace alx {


/**
    Shared-based wrapper class around ALLEGRO_USTR.
 */
class String : public Shared<ALLEGRO_USTR> {
public:
    /**
        Null string constructor.
     */
    String() {
    }

    /**
        Constructor from null-terminated string.
        @param str string.
     */
    String(const char *str) : Shared(al_ustr_new(str), al_ustr_free) {
    }

    /**
        Constructor from null-terminated string buffer.
        @param str string buffer.
        @param size number of characters.
     */
    String(const char *str, size_t size) : Shared(al_ustr_new_from_buffer(str, size), al_ustr_free) {
    }

    /**
        Constructor from null-terminated wide character string.
        @param str string.
     */
    String(const wchar_t *str) : Shared(al_ustr_new(_toUTF8(str).c_str()), al_ustr_free) {
    }

    /**
        Constructor from null-terminated wide character string buffer.
        @param str string buffer.
        @param size number of characters.
     */
    String(const wchar_t *str, size_t size) : Shared(al_ustr_new(_toUTF8(str, size).c_str()), al_ustr_free) {
    }

    /**
        Constructor from character.
        @param c character.
     */
    String(char c) {
        printf("%c", c);
    }

    /**
        Constructor from wide character.
        @param c character.
     */
    String(wchar_t c) {
        char s[5];
        size_t sz = al_utf8_encode(s, c);
        s[sz] = '\0';
        printf("%s", s);
    }

    /**
        Constructor from 32-bit integer.
        @param i integer.
     */
    String(int32_t i) {
        printf("%i", i);
    }

    /**
        Constructor from 64-bit integer.
        @param i integer.
     */
    String(int64_t i) {
        printf("%lli", i);
    }

    /**
        Constructor from 32-bit unsigned integer.
        @param u unsigned integer.
     */
    String(uint32_t u) {
        printf("%u", u);
    }

    /**
        Constructor from 64-bit unsigned integer.
        @param u unsigned integer.
     */
    String(uint64_t u) {
        printf("%llu", u);
    }

    /**
        Constructor from double float.
        @param d double float.
     */
    String(double d) {
        printf("%f", d);
    }

    /**
        Constructor from long double float.
        @param d long double float.
     */
    String(long double d) {
        printf("%Lf", d);
    }

    /**
        Constructor from pointer.
        @param p pointer.
     */
    String(void *p) {
        printf("%p", p);
    }

    /**
        Constructor from fixed.
        @param f fixed.
     */
    String(Fixed f) {
        printf("%f", (double)f);
    }

    /**
        Constructor from substring of null-terminated string.
        @param str string.
        @param index index.
        @param size size.
     */
    String(const char *str, size_t index, size_t size) {
        assign(str, index, size);
    }

    /**
        Constructor from substring of null-terminated string.
        @param str string.
        @param index index.
        @param size size.
     */
    String(const wchar_t *str, size_t index, size_t size) {
        assign(str, index, size);
    }

    /**
        Returns a temporary pointer to a null-terminated string.
        @return a temporary pointer to a null-terminated string.
     */
    const char *cstr() const {
        return al_cstr(get());
    }

    /**
        Returns a temporary pointer to a null-terminated string.
        @return a temporary pointer to a null-terminated string.
     */
    operator const char *() const {
        return cstr();
    }

    /**
        Copies the string to the given buffer.
        @param buffer pointer to buffer.
        @param size buffer size.
     */
    void toBuffer(char *buffer, size_t size) const {
        al_ustr_to_buffer(get(), buffer, size);
    }

    /**
        Clones the string.
        @return a copy of this string.
     */
    String clone() const {
        return al_ustr_dup(get());
    }

    /**
        Returns a substring.
        @param startOffset start offset.
        @param endOffset end offset.
        @return substring.
     */
    String subString(int startOffset, int endOffset) const {
        ALLEGRO_USTR *str = al_ustr_dup_substr(get(), startOffset, endOffset);
        String result = str;
        return result;
    }

    /**
        Returns the empty string.
        @return the empty string.
     */
    static String emptyString() {
        return al_ustr_dup(al_ustr_empty_string());
    }

    /**
        Returns the number of bytes the string occupies.
        @return the number of bytes the string occupies.
     */
    size_t getSize() const {
        return al_ustr_size(get());
    }

    /**
        Returns the number of code points the string contains.
        @return the number of code points the string contains.
     */
    size_t getLength() const {
        return al_ustr_length(get());
    }

    /**
        Returns true if the length of the string is zero or it is null.
        @return
     */
    bool isEmpty() const {
        return al_ustr_length(get()) == 0;
    }

    /**
        Returns the byte offset of the code point index.
        @param codePointIndex index of the code point.
        @return the byte offset of the code point index.
     */
    int getOffset(int codePointIndex) const {
        return al_ustr_offset(get(), codePointIndex);
    }

    /**
        Returns the prevois code point offset.
        @param offset start offset.
        @return new offset.
     */
    int getPrevOffset(int offset) const {
        al_ustr_prev(get(), &offset);
        return offset;
    }

    /**
        Returns the next code point offset.
        @param offset start offset.
        @return new offset.
     */
    int getNextOffset(int offset) const {
        al_ustr_next(get(), &offset);
        return offset;
    }

    /**
        Returns the code point at the given offset.
        @param offset offset.
        @return the code point.
     */
    int32_t getCodePoint(int offset) const {
        return al_ustr_get(get(), offset);
    }

    /**
        Searches the string for the given code point, then returns its offset.
        @param cp code point to find.
        @param offset offset to start from.
        @return offset the code point is found at or -1 if not found.
     */
    int find(uint32_t cp, int offset = 0) const {
        return al_ustr_find_chr(get(), offset, cp);
    }

    /**
        Searches the string for the given string, then returns its offset.
        @param str string to find.
        @param offset offset to start from.
        @return offset the string is found at or -1 if not found.
     */
    int find(const String &str, int offset = 0) const {
        return al_ustr_find_str(get(), offset, str.get());
    }

    /**
        Searches the string for the given code point, then returns its offset.
        @param cp code point to find.
        @param offset offset to start from.
        @return offset the code point is found at or -1 if not found.
     */
    int findReverse(uint32_t cp, int offset = 0) const {
        return al_ustr_rfind_chr(get(), offset >= 0 ? offset : al_ustr_size(get()), cp);
    }

    /**
        Searches the string for the given string, then returns its offset.
        @param str string to find.
        @param offset offset to start from; if -1, the search starts from the end of the string.
        @return offset the string is found at or -1 if not found.
     */
    int findReverse(const String &str, int offset = -1) const {
        return al_ustr_rfind_str(get(), offset >= 0 ? offset : al_ustr_size(get()), str.get());
    }

    /**
        Equality check.
        @param str string.
        @return true if the test is successful.
     */
    bool operator == (const String &str) const {
        return al_ustr_equal(get(), str.get());
    }

    /**
        Difference check.
        @param str string.
        @return true if the test is successful.
     */
    bool operator != (const String &str) const {
        return !operator == (str);
    }

    /**
        Less-than check.
        @param str string.
        @return true if the test is successful.
     */
    bool operator < (const String &str) const {
        return al_ustr_compare(get(), str.get()) < 0;
    }

    /**
        Less-than or equal check.
        @param str string.
        @return true if the test is successful.
     */
    bool operator <= (const String &str) const {
        return al_ustr_compare(get(), str.get()) <= 0;
    }

    /**
        Greater-than check.
        @param str string.
        @return true if the test is successful.
     */
    bool operator > (const String &str) const {
        return al_ustr_compare(get(), str.get()) > 0;
    }

    /**
        Greater-than or equal check.
        @param str string.
        @return true if the test is successful.
     */
    bool operator >= (const String &str) const {
        return al_ustr_compare(get(), str.get()) >= 0;
    }

    /**
        Tests if the string starts with the given string.
        @param str the string to check for.
        @return true if it starts with the given string.
     */
    bool startsWith(const String &str) const {
        return al_ustr_has_prefix(get(), str.get());
    }

    /**
        Tests if the string ends with the given string.
        @param str the string to check for.
        @return true if it ends with the given string.
     */
    bool endsWith(const String &str) const {
        return al_ustr_has_suffix(get(), str.get());
    }

    /**
        Printf.
        @param format format string.
        @param ... printf arguments.
        @return true on success.
     */
    bool printf(const char *format, ...) {
        va_list args;
        va_start(args, format);
        bool ok = printf(format, args);
        va_end(args);
        return ok;
    }

    /**
        Printf.
        @param format format string.
        @param args printf arguments.
        @return true on success.
     */
    bool printf(const char *format, va_list args) {
        reset(al_ustr_new(""), al_ustr_free);
        return al_ustr_vappendf(get(), format, args);
    }

    /**
        Adds a string to this string.
        @param a 1st string.
        @param b 2nd string.
        @return a string that contains both strings.
     */
    template <class T> friend String operator + (const String &a, const T &b) {
        return a.clone() += String(b);
    }

    /**
        inserts the given string at the givven offset.
        @param str string to insert.
        @param offset offset.
        @return true on success.
     */
    bool insert(const String &str, int offset) {
        return al_ustr_insert(get(), offset, str.get());
    }

    /**
        Adds the given string at the beginning of this one.
        @param str string to insert.
        @return true on success.
     */
    bool prepend(const String &str) {
        return insert(str, 0);
    }

    /**
        Removes a code point at the specified offset.
        @param offset offset.
        @return true on success.
     */
    bool remove(int offset) {
        return al_ustr_remove_chr(get(), offset);
    }

    /**
        Removes multiple code points between the given ranges.
        @param startOffset start offset.
        @param endOffset end offset.
        @return true on success.
     */
    bool remove(int startOffset, int endOffset) {
        return al_ustr_remove_range(get(), startOffset, endOffset);
    }

    /**
        Replaces the code point at the specified position.
        @param offset offset.
        @param cp new code point.
        @return true on success.
     */
    bool replace(int offset, int32_t cp) {
        return al_ustr_set_chr(get(), offset, cp) > 0;
    }

    /**
        Replaces part of the string with the given one.
        @param startOffset start offset.
        @param endOffset end offset.
        @param str new string.
        @return true on success.
     */
    bool replace(int startOffset, int endOffset, const String &str) {
        return al_ustr_replace_range(get(), startOffset, endOffset, str.get());
    }

    /**
        Trim leading whitespace.
     */
    bool trimLeadingWhitespace() {
        return al_ustr_ltrim_ws(get());
    }

    /**
        Trim trailing whitespace.
     */
    bool trimTrailingWhitespace() {
        return al_ustr_rtrim_ws(get());
    }

    /**
        Trim leading and trailing whitespace.
     */
    bool trimWhitespace() {
        return al_ustr_trim_ws(get());
    }

    /*
     * STL INTERFACE
     */

    /**
        Base class for a code point reference.
     */
    class CodePointRefBase {
    public:
        /**
            constructor.
            @param str allegro string to iterate over.
            @param offset offset.
         */
        CodePointRefBase(ALLEGRO_USTR *str = nullptr, int offset = 0) : m_string(str), m_offset(offset) {
        }

        /**
            Returns the allegro string.
            @return the allegro string.
         */
        ALLEGRO_USTR *getString() const {
            return m_string;
        }

        /**
            Returns the offset.
            @return the offset.
         */
        int getOffset() const {
            return m_offset;
        }

    protected:
        /**
            String.
         */
        ALLEGRO_USTR *m_string;

        /**
            Offset.
         */
        int m_offset;
    };

    /**
        iterator base class.
     */
    template <class T, class E> class iterator_base : public CodePointRefBase, public std::iterator<std::bidirectional_iterator_tag, E, ptrdiff_t, E*, E> {
    public:
        /**
            constructor.
            @param str allegro string to iterate over.
            @param offset offset.
         */
        iterator_base(ALLEGRO_USTR *str = nullptr, int offset = 0) : CodePointRefBase(str, offset) {
        }

        /**
            Checks if the given iterator points to the same string position.
            @param it the other iterator.
            @return true if they point to the same position, false otherwise.
         */
        bool operator == (const iterator_base &it) const {
            return m_string == it.m_string && m_offset == it.m_offset;
        }

        /**
            Checks if the given iterator points to a different string position.
            @param it the other iterator.
            @return true if they point to a different string position, false otherwise.
         */
        bool operator != (const iterator_base &it) const {
            return !operator == (it);
        }

        /**
            Advances the iterator to the next code point.
            @return reference to this.
         */
        T &operator ++() {
            al_ustr_next(m_string, &m_offset);
            return *static_cast<T *>(this);
        }

        /**
            Advances the iterator to the previous code point.
            @return reference to this.
         */
        T &operator --() {
            al_ustr_prev(m_string, &m_offset);
            return *static_cast<T *>(this);
        }
    };

    /**
        Constant iterator.
     */
    class const_iterator : public iterator_base<const_iterator, int32_t> {
    public:
        /**
            constructor.
            @param str allegro string to iterate over.
            @param offset offset.
         */
        const_iterator(ALLEGRO_USTR *str = nullptr, int offset = 0) : iterator_base(str, offset) {
        }

        /**
            Returns the code point at the current offset.
            @return the code point at the current offset.
         */
        int32_t operator *() const {
            return al_ustr_get(m_string, m_offset);
        }
    };

    class iterator;

    /**
        Reference to a code point.
     */
    class CodePointRef : public CodePointRefBase {
    public:
        /**
            constructor.
            @param str allegro string to iterate over.
            @param offset offset.
         */
        CodePointRef(ALLEGRO_USTR *str = nullptr, int offset = 0) : CodePointRefBase(str, offset) {
        }

        /**
            Conversion to code point.
            @return code point.
         */
        operator int32_t () const {
            return al_ustr_get(m_string, m_offset);
        }

        /**
            Replaces the code point at the specific reference.
            @param cp new code point.
            @return reference to this.
         */
        CodePointRef &operator = (int32_t cp) {
            al_ustr_set_chr(m_string, m_offset, cp);
            return *this;
        }
    };

    /**
        iterator.
     */
    class iterator : public iterator_base<iterator, CodePointRef> {
    public:
        /**
            constructor.
            @param str allegro string to iterate over.
            @param offset offset.
         */
        iterator(ALLEGRO_USTR *str = nullptr, int offset = 0) : iterator_base(str, offset) {
        }

        /**
            Returns a code point reference at the current offset.
            @return a code point reference at the current offset.
         */
        CodePointRef operator *() const {
            return CodePointRef(m_string, m_offset);
        }
    };

    /**
        Reverse iterator.
     */
    typedef std::reverse_iterator<iterator> reverse_iterator;

    /**
        const reverse iterator.
     */
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    /**
        Substring constructor.
        @param str source string.
        @param index start character index.
        @param len of characters; if -1, the whole string.
     */
    String(const String &str, size_t index, size_t len = -1) :
        Shared(al_ustr_dup_substr(str.get(), al_ustr_offset(str.get(), index), al_ustr_offset(str.get(), len >= 0 ? index + len : INT_MAX)), al_ustr_free)
    {
    }

    /**
        Fills the string with the given number of characters.
        @param n number of characters.
        @param cp code point.
     */
    String(size_t n, int32_t cp) : Shared(al_ustr_new(""), al_ustr_free) {
        do {
            al_ustr_append_chr(get(), cp);
        } while (--n > 0);
    }

    /**
        Construct string from iterator pair.
        @param first first.
        @param last last (exclusive).
     */
    template <class InputIterator> String(const InputIterator &first, const InputIterator &last) :
        Shared(al_ustr_new(""), al_ustr_free)
    {
        for(InputIterator it = first; it != last; ++it) {
            al_ustr_append_chr(get(), *it);
        }
    }

    /**
        constructor from initializer list.
        @param il initializer list.
     */
    template <class T> String(std::initializer_list<T> il) :
        Shared(al_ustr_new(""), al_ustr_free)
    {
        for(auto cp : il) {
            al_ustr_append_chr(get(), cp);
        }
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    const_iterator begin() const {
        return const_iterator(get(), 0);
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    const_iterator end() const {
        return const_iterator(get(), al_ustr_size(get()));
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    iterator begin() {
        return iterator(get(), 0);
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    iterator end() {
        return iterator(get(), al_ustr_size(get()));
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    const_iterator cbegin() const {
        return const_iterator(get(), 0);
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    const_iterator cend() const {
        return const_iterator(get(), al_ustr_size(get()));
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    const_iterator cbegin() {
        return const_iterator(get(), 0);
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    const_iterator cend() {
        return const_iterator(get(), al_ustr_size(get()));
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    const_reverse_iterator crend() const {
        return const_reverse_iterator(begin());
    }

    /**
        Returns an iterator that points to the beginning element.
        @return an iterator that points to the beginning element.
     */
    const_reverse_iterator crbegin() {
        return const_reverse_iterator(cend());
    }

    /**
        Returns an iterator that points to the end element.
        @return an iterator that points to the end element.
     */
    const_reverse_iterator crend() {
        return const_reverse_iterator(cbegin());
    }

    /**
        returns the string's length.
        @return the string's length.
     */
    size_t size() const {
        return getLength();
    }

    /**
        returns the string's length.
        @return the string's length.
     */
    size_t length() const {
        return getLength();
    }

    /**
        Returns UINT_MAX.
     */
    size_t max_size() const {
        return UINT_MAX;
    }

    /**
        Resizes the string to N code points.
        @param n number of code points.
     */
    void resize(size_t n) {
        resize(n, ' ');
    }

    /**
        Resizes the string to N code points, filling the new code points with the given code point.
        @param n number of code points.
        @param cp new code points.
     */
    void resize(size_t n, int32_t cp) {
        size_t len = length();
        if (n < len) operator = (String(*this, 0, n));
        else if (n > len) operator += (String(n - len, cp));
    }

    /**
        Same as length.
        @return the capacity, i.e. length of the string.
     */
    size_t capacity() const {
        return length();
    }

    /**
        simply resizes the string to the given value.
        @param n new number of characters.
     */
    void reserve(size_t n = 0) {
        resize(n);
    }

    /**
        Makes the string null.
     */
    void clear() {
        reset();
    }

    /**
        Checks if the string is empty.
        @return true if empty.
     */
    bool empty() const {
        return isEmpty();
    }

    /**
        Does nothing.
     */
    void shrink_to_fit() {
    }

    /**
        Returns code point at given index.
        @return code point at given index.
     */
    int32_t operator [](size_t index) const {
        return al_ustr_get(get(), al_ustr_offset(get(), index));
    }

    /**
        Returns code point reference at given index.
        @return code point reference at given index.
     */
    CodePointRef operator [](size_t index) {
        return CodePointRef(get(), al_ustr_offset(get(), index));
    }

    /**
        Returns code point at given index.
        @return code point at given index.
        @exception std::out_of_range thrown if the index is out of range.
     */
    int32_t at(size_t index) const {
        if (index >= length()) throw std::out_of_range("invalid alx::String index");
        return al_ustr_get(get(), al_ustr_offset(get(), index));
    }

    /**
        Returns code point reference at given index.
        @return code point reference at given index.
        @exception std::out_of_range thrown if the index is out of range.
     */
    CodePointRef at(size_t index) {
        if (index >= length()) throw std::out_of_range("invalid alx::String index");
        return CodePointRef(get(), al_ustr_offset(get(), index));
    }

    /**
        Returns the last code point.
        @return the last code point.
     */
    int32_t back() const {
        int offset = al_ustr_size(get());
        return al_ustr_prev_get(get(), &offset);
    }

    /**
        Returns a reference to the last code point.
        @return a reference to the last code point.
     */
    CodePointRef back() {
        int offset = al_ustr_size(get());
        al_ustr_prev_get(get(), &offset);
        return CodePointRef(get(), offset);
    }

    /**
        Returns the first code point.
        @return the first code point.
     */
    int32_t front() const {
        return al_ustr_get(get(), 0);
    }

    /**
        Returns a reference to the first code point.
        @return a reference to the first code point.
     */
    CodePointRef front() {
        return CodePointRef(get(), 0);
    }

    /**
        Appends a string.
        @param str string to append.
        @return reference to this.
     */
    String &operator += (const char *str) {
        if (get()) al_ustr_append_cstr(get(), str); else operator = (str);
        return *this;
    }

    /**
        Appends a string.
        @param str string to append.
        @return reference to this.
     */
    String &operator += (const String &str) {
        if (get()) al_ustr_append(get(), str.get()); else operator = (str.clone());
        return *this;
    }

    /**
        Appends a code point.
        @param cp code point to append.
        @return reference to this.
     */
    String &operator += (int32_t cp) {
        if (get()) al_ustr_append_chr(get(), cp); else operator = (cp);
        return *this;
    }

    /**
        Adds the given string at the end of this one.
        @param str string to insert.
        @return reference to this.
     */
    String &append(const String &str) {
        al_ustr_append(get(), str.get());
        return *this;
    }

    /**
        Adds a subtring the given string at the end of this one.
        @param str string to insert.
        @param offset byte offset.
        @param size byte size.
        @return reference to this.
     */
    String &append(const String &str, size_t offset, size_t size) {
        ALLEGRO_USTR_INFO info;
        const ALLEGRO_USTR *substr = al_ref_ustr(&info, str.get(), offset, offset + size);
        al_ustr_append(get(), substr);
        return *this;
    }

    /**
        Adds the given string at the end of this one.
        @param str string to insert.
        @return reference to this.
     */
    String &append(const char *str) {
        al_ustr_append_cstr(get(), str);
        return *this;
    }

    /**
        Adds part of the given string at the end of this one.
        @param str string to insert.
        @param size number of characters to add.
        @return reference to this.
     */
    String &append(const char *str, size_t size) {
        ALLEGRO_USTR_INFO info;
        const ALLEGRO_USTR *substr = al_ref_buffer(&info, str, size);
        al_ustr_append(get(), substr);
        return *this;
    }

    /**
        Adds the given code point at the end of the string multiple times.
        @param count number of code points to append.
        @param cp code point to append.
        @return reference to this.
     */
    String &append(size_t count, int32_t cp) {
        if (count > 0) {
            operator += (cp);
            for(; count > 1; --count) {
                al_ustr_append_chr(get(), cp);
            }
        }
        return *this;
    }

    /**
        Appends the given range.
        @param first iterator that points to the first element.
        @param last iterator that points to the end element; exclusive.
        @return reference to this.
     */
    template <class It> String &append(const It &first, const It &last) {
        for(It it = first; it != last; ++it) {
            operator += (*it);
        }
        return *this;
    }

    /**
        Adds a subtring the given string at the end of this one.
        @param str string to insert.
        @param index index.
        @param size ize.
        @return reference to this.
     */
    String &append(const char *str, size_t index, size_t size) {
        ALLEGRO_USTR_INFO info;
        const ALLEGRO_USTR *substr = al_ref_buffer(&info, str + index, size);
        al_ustr_append(get(), substr);
        return *this;
    }

    /**
        Adds a subtring the given string at the end of this one.
        @param str string to insert.
        @param index index.
        @param size ize.
        @return reference to this.
     */
    String &append(const wchar_t *str, size_t index, size_t size) {
        return append(str + index, str + index + size);
    }

    /**
        Pushes back a code point.
        @param c code point.
     */
    void push_back(int32_t c) {
        operator += (c);
    }

    /**
        Assigns the given string to this.
        @param str string to insert.
        @return reference to this.
     */
    String &assign(const String &str) {
        return operator = (str);
    }

    /**
        Assigns a subtring of the given string to this.
        @param str string to insert.
        @param offset byte offset.
        @param size byte size.
        @return reference to this.
     */
    String &assign(const String &str, size_t offset, size_t size) {
        ALLEGRO_USTR_INFO info;
        const ALLEGRO_USTR *substr = al_ref_ustr(&info, str.get(), offset, offset + size);
        reset(al_ustr_dup(substr), al_ustr_free);
        return operator = (String());
    }

    /**
        Assigns the given string to this.
        @param str string to insert.
        @return reference to this.
     */
    String &assign(const char *str) {
        reset(al_ustr_new(str), al_ustr_free);
        return *this;
    }

    /**
        Assigns part of the given string to this.
        @param str string to insert.
        @param size number of characters to add.
        @return reference to this.
     */
    String &assign(const char *str, size_t size) {
        reset(al_ustr_new_from_buffer(str, size), al_ustr_free);
        return *this;
    }

    /**
        Assigns the given code point at the end of the string multiple times.
        @param count number of code points to assign.
        @param cp code point to assign.
        @return reference to this.
     */
    String &assign(size_t count, int32_t cp) {
        clear();
        append(count, cp);
        return *this;
    }

    /**
        Appends the given range.
        @param first iterator that points to the first element.
        @param last iterator that points to the end element; exclusive.
        @return reference to this.
     */
    template <class It> String &assign(const It &first, const It &last) {
        clear();
        append(first, last);
        return *this;
    }

    /**
        Assigns a subtring the given string to this.
        @param str string to insert.
        @param index index.
        @param size ize.
        @return reference to this.
     */
    String &assign(const char *str, size_t index, size_t size) {
        reset(al_ustr_new_from_buffer(str + index, size), al_ustr_free);
        return *this;
    }

    /**
        Assigns a subtring the given string to this.
        @param str string to insert.
        @param index index.
        @param size ize.
        @return reference to this.
     */
    String &assign(const wchar_t *str, size_t index, size_t size) {
        return assign(str + index, str + index + size);
    }

    //TODO rest of std::string functions

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    String(ALLEGRO_USTR *object, bool managed = true) : Shared(object, managed, al_ustr_free) {
    }

    /**
        Split the string by a character.
     */
    std::vector<String> split(int32_t c) const {
        ALLEGRO_USTR *str = get();

        int startPos = 0;
        int currPos = 0;

        std::vector<String> result;

        for(;;) {
            int tempCurrPos = currPos;
            int32_t currChar = al_ustr_get_next(str, &tempCurrPos);

            //end of sequence or error
            if (currChar < 0) {
                String str = subString(startPos, currPos);
                str.trimWhitespace();
                result.push_back(str);
                break;
            }

            //found character
            if (currChar == c) {
                String str = subString(startPos, currPos);
                str.trimWhitespace();
                result.push_back(str);
                startPos = tempCurrPos;
            }

            //next position
            currPos = tempCurrPos;
        }

        return result;
    }

private:
    //convert wide character string to utf8
    static std::string _toUTF8(const wchar_t *str) {
        std::string result;
        for(; *str; ++str) {
            char s[5];
            size_t sz = al_utf8_encode(s, *str);
            s[sz] = '\0';
            result += s;
        }
        return result;
    }

    //convert wide character string to utf8
    static std::string _toUTF8(const wchar_t *str, size_t size) {
        std::string result;
        for(const wchar_t *end = str + size; str < end; ++str) {
            char s[5];
            size_t sz = al_utf8_encode(s, *str);
            s[sz] = '\0';
            result += s;
        }
        return result;
    }
};


} //namespace alx


namespace std {


/**
    Hash function for alx::String.
 */
template <> struct hash<alx::String> {
public:
    size_t operator ()(const alx::String &str) const {
        return std::hash<std::string>()(str.cstr());
    }
};


} //namespace std


/**
    Outputs a String to an std::stream.
    @param stream stream.
    @param str string.
    @return reference to string.
 */
template <class E, class TR = std::char_traits<E>> std::basic_ostream<E, TR> &operator << (std::basic_ostream<E, TR> &stream, const alx::String &str) {
    stream << str.cstr();
    return stream;
}


/**
    Inputs a String from an std::stream.
    @param stream stream.
    @param str string.
    @return reference to string.
 */
template <class E, class TR = std::char_traits<E>> std::basic_ostream<E, TR> &operator >> (std::basic_ostream<E, TR> &stream, alx::String &str) {
    std::basic_string<E, TR> temp;
    stream >> temp;
    str = temp;
    return stream;
}


#endif //ALX_STRING_HPP
