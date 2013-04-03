#ifndef ALX_FILE_HPP
#define ALX_FILE_HPP


#include <vector>
#include <array>
#include <algorithm>
#include "String.hpp"


#ifdef min
#undef min
#endif


namespace alx {


//TODO


/**
    Value-based wrapper around ALLEGRO_FILE.
 */
class File {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    File(ALLEGRO_FILE *object, bool managed = true) : m_object(object, managed ? al_fclose : [](ALLEGRO_FILE *){}) {
    }

    /**
        Opens a file.
        @param path path.
        @param mode mode.
     */
    File(const char *path, const char *mode) : m_object(al_fopen(path, mode), al_fclose) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        opens the file.
        @param path path.
        @param mode mode.
        @return true on success.
     */
    bool open(const char *path, const char *mode) {
        m_object = std::shared_ptr<ALLEGRO_FILE>(al_fopen(path, mode), al_fclose);
        return m_object;
    }

    /**
        closes the file.
     */
    void close() {
        al_fclose(m_object.get());
    }

    /**
        Flushes any pending writes.
        @return true on success.
     */
    bool flush() {
        al_fflush(m_object.get());
    }

    /**
        Returns the file position (the 'ftell' function).
        @return the file position.
     */
    int64_t getFilePosition() const {
        return al_ftell(m_object.get());
    }

    /**
        Sets the file position (the 'fseek' function).
        @param pos position.
        @param from the 'whence' parameter: ALLEGRO_SEEK_SET, ALLEGRO_SEEK_CUR, ALLEGRO_SEEK_END.
     */
    bool setFilePosition(int64_t pos, int from = ALLEGRO_SEEK_SET) {
        return al_fseek(m_object.get(), pos, from);
    }

    /**
        Checks if the EOF indicator has been set.
        @return true if set.
     */
    bool isEOF() const {
        return al_feof(m_object.get());
    }

    /**
        Checks if the error indicator has been set.
        @return true if set.
     */
    bool isError() const {
        return al_ferror(m_object.get());
    }

    /**
        Clears the error.
     */
    void clearError() {
        al_fclearerr(m_object.get());
    }

    /**
        Returns the size of the file.
        @return the size of the file.
     */
    int64_t getSize() const {
       return al_fsize(m_object.get());
    }
    
    /**
        Reads raw bytes into a buffer.
        @param dst destination buffer; it must have enough space to read the given data.
        @param size number of bytes to read.
        @return the number of bytes actually read.
     */
    size_t read(void *dst, size_t size) {
        return al_fread(m_object.get(), dst, size);
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
        Writes raw bytes to the file.
        @param src source buffer.
        @param size number of bytes to write.
        @return number of bytes actually written.
     */
    size_t write(const void *src, size_t size) {
        return al_fwrite(m_object.get(), src, size);
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

    //TODO read/write primitive values


private:
    //internal allegro object.
    std::shared_ptr<ALLEGRO_FILE> m_object;

    friend class Config;
};


} //namespace alx


#endif //ALX_FILE_HPP
