#ifndef ALX_FILE_HPP
#define ALX_FILE_HPP


#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <tuple>
#include "String.hpp"
#include "Util.hpp"
#include "FilePath.hpp"


#ifdef min
#undef min
#endif


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_FILE.
 */
class File : public Shared<ALLEGRO_FILE> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    File(ALLEGRO_FILE *object, bool managed = true) : Shared(object, managed, al_fclose, [](ALLEGRO_FILE *){}) {
    }

    /**
        null file constructor.
     */
    File() {
    }

    /**
        Opens a file.
        @param path path.
        @param mode mode.
     */
    File(const char *path, const char *mode) : Shared(al_fopen(path, mode), al_fclose) {
    }

    /**
        Opens a file.
        @param fd file descriptor.
        @param mode mode.
     */
    File(int fd, const char *mode) : Shared(al_fopen_fd(fd, mode), al_fclose) {
    }

    /**
        opens a file.
        @param path path.
        @param mode mode.
        @return true on success.
     */
    bool open(const char *path, const char *mode) {
        reset(al_fopen(path, mode), al_fclose);
        return *this;
    }

    /**
        opens a file.
        @param int fd file descriptor.
        @param mode mode.
        @return true on success.
     */
    bool open(int fd, const char *mode) {
        reset(al_fopen_fd(fd, mode), al_fclose);
        return *this;
    }

    /**
        closes the file.
     */
    void close() {
        al_fclose(get());
    }

    /**
        Flushes any pending writes.
        @return true on success.
     */
    bool flush() {
        al_fflush(get());
    }

    /**
        Returns the file position (the 'ftell' function).
        @return the file position.
     */
    int64_t getFilePosition() const {
        return al_ftell(get());
    }

    /**
        Sets the file position (the 'fseek' function).
        @param pos position.
        @param from the 'whence' parameter: ALLEGRO_SEEK_SET, ALLEGRO_SEEK_CUR, ALLEGRO_SEEK_END.
     */
    bool setFilePosition(int64_t pos, int from = ALLEGRO_SEEK_SET) {
        return al_fseek(get(), pos, from);
    }

    /**
        Checks if the EOF indicator has been set.
        @return true if set.
     */
    bool isEOF() const {
        return al_feof(get());
    }

    /**
        Checks if the error indicator has been set.
        @return true if set.
     */
    bool isError() const {
        return al_ferror(get());
    }

    /**
        Clears the error.
     */
    void clearError() {
        al_fclearerr(get());
    }

    /**
        Returns the size of the file.
        @return the size of the file.
     */
    int64_t getSize() const {
       return al_fsize(get());
    }
    
    /**
        Reads raw bytes into a buffer.
        @param dst destination buffer; it must have enough space to read the given data.
        @param size number of bytes to read.
        @return the number of bytes actually read.
     */
    size_t read(void *dst, size_t size) {
        return al_fread(get(), dst, size);
    }

    /**
        Reads raw bytes into a static array.
        It reads no more than the size that the array can hold. 
        @param dst destination buffer.
        @param size number of bytes to read.
        @return the number of bytes actually read.
     */
    template <class T, size_t BUFFER_SIZE> size_t read(std::array<T, BUFFER_SIZE> &dst, size_t size) {
        return read(&dst[0], std::min(BUFFER_SIZE * sizeof(T), size));
    }

    /**
        Reads raw bytes into a dynamic array.
        It reads no more than the size that the array can hold. 
        @param dst destination buffer.
        @param size number of bytes to read.
        @return the number of bytes actually read.
     */
    template <class T, class A> size_t read(std::vector<T, A> &dst, size_t size) {
        return read(&dst[0], std::min(dst.size() * sizeof(T), size));
    }

    /**
        Reads a single value from the file.
        @param v destination variable.
        @return true on success.
     */
    template <bool LittleEndian = true, class T> bool read(T &v) {
        if (!read(&v, sizeof(T))) return false;
        if (LittleEndian) v = Util::littleToNativeEndian(v); else v = Util::bigToNativeEndian(v);
        return true;
    }

    /**
        Reads a single value from the file.
        @param v destination variable.
        @return this file.
        @exception std::runtime_error thrown if there was an error reading the value.
     */
    template <class T> File &operator >> (T &v) {
        if (read(v)) return *this;
        throw std::runtime_error("File I/O error");
    }

    /**
        Reads a line of text.
        @param v destination variable.
        @return true on success.
     */
    bool read(String &v) {
        ALLEGRO_USTR *str = al_fget_ustr(get());
        if (!str) return false;
        v = str;
        return true;
    }

    /**
        Reads a line of text.
        @param v destination variable.
        @return true on success.
        @exception std::runtime_error thrown if there was an error reading the line.
     */
    File &operator >> (String &v) {
        if (read(v)) return *this;
        throw std::runtime_error("File I/O error");
    }

    /**
        Writes raw bytes to the file.
        @param src source buffer.
        @param size number of bytes to write.
        @return number of bytes actually written.
     */
    size_t write(const void *src, size_t size) {
        return al_fwrite(get(), src, size);
    }

    /**
        Writes raw bytes from a static array.
        It writes no more than the size that the array can hold. 
        @param src source buffer.
        @param size number of bytes to write.
        @return the number of bytes actually written.
     */
    template <class T, size_t BUFFER_SIZE> size_t write(const std::array<T, BUFFER_SIZE> &src, size_t size) {
        return write(&src[0], std::min(BUFFER_SIZE * sizeof(T), size));
    }

    /**
        Writes raw bytes from a dynamic array.
        It writes no more than the size that the array can hold. 
        @param src source buffer.
        @param size number of bytes to write.
        @return the number of bytes actually written.
     */
    template <class T, class A> size_t write(const std::vector<T, A> &src, size_t size) {
        return write(&src[0], std::min(src.size() * sizeof(T), size));
    }

    /**
        Writes a single value to the file.
        @param v source value.
        @return true on success.
     */
    template <bool LittleEndian = true, class T> bool write(T v) {
        if (LittleEndian) v = Util::nativeToLittleEndian(v); else v = Util::nativeToBigEndian(v);
        return write(&v, sizeof(T));
    }

    /**
        Writes a single value to the file.
        @param v source value.
        @return this file.
        @exception std::runtime_error thrown if there was an error writing the value.
     */
    template <class T> File &operator << (T v) {
        if (write(v)) return *this;
        throw std::runtime_error("File I/O error");
    }

    /**
        Writes a string to the file.
        @param v string to write.
        @return true on success.
     */
    bool write(const String &v) {
        return al_fputs(get(), v.cstr()) >= 0;
    }

    /**
        Writes a string to the file.
        @param v string to write.
        @return this file.
        @exception std::runtime_error thrown if there was an error writing the value.
     */
    File &operator << (const String &v) {
        if (write(v)) return *this;
        throw std::runtime_error("File I/O error");
    }

    /**
        Creates a temporary file.
        @param filenameTemplate the template for the filename.
     */
    static std::tuple<File, FilePath> createTempFile(const char *filenameTemplate) {
        ALLEGRO_PATH *path = nullptr;
        ALLEGRO_FILE *file = al_make_temp_file(filenameTemplate, &path);       
        return std::make_tuple(file, path); 
    }
};


} //namespace alx


#endif //ALX_FILE_HPP
