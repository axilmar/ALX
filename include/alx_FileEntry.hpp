#ifndef ALX_FILEENTRY_HPP
#define ALX_FILEENTRY_HPP


#include <allegro5/allegro.h>
#include "alx_Shared.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_FS_ENTRY.
 */
class FileEntry : public Shared<ALLEGRO_FS_ENTRY> {
public:
    /**
        A null file entry.
     */
    FileEntry() {
    }

    /**
        constructor from path.
        @param path file path.
     */
    FileEntry(const char *path) : Shared(al_create_fs_entry(path), al_destroy_fs_entry) {
    }

    /**
        Returns the path of the file entry.
        @return the path of the file entry.
     */
    String getPath() const {
        return al_ustr_new(al_get_fs_entry_name(get()));
    }

    /**
        Returns the entry's mode flags.
        @return the mode flags.
     */
    uint32_t getMode() const {
        return al_get_fs_entry_mode(get());
    }

    /**
        Checks if the file is readable.
        @return true if readable.
     */
    bool isReadable() const {
        return (getMode() && ALLEGRO_FILEMODE_READ) != 0;
    }

    /**
        Checks if the file is writable.
        @return true if writable.
     */
    bool isWritable() const {
        return (getMode() && ALLEGRO_FILEMODE_WRITE) != 0;
    }

    /**
        Checks if the file is executable.
        @return true if executable.
     */
    bool isExecutable() const {
        return (getMode() && ALLEGRO_FILEMODE_EXECUTE) != 0;
    }

    /**
        Checks if the file is hidden.
        @return true if visible.
     */
    bool isHidden() const {
        return (getMode() && ALLEGRO_FILEMODE_HIDDEN) != 0;
    }

    /**
        Checks if the file is not a directory.
        @return true if not a directory.
     */
    bool isFile() const {
        return (getMode() && ALLEGRO_FILEMODE_ISFILE) != 0;
    }

    /**
        Checks if the file is a directory.
        @return true if a directory.
     */
    bool isDirectory() const {
        return (getMode() && ALLEGRO_FILEMODE_ISDIR) != 0;
    }

    /**
        Returns the entry's last access time.
        @return the entry's last access time.
     */
    time_t getAccessTime() const {
        return al_get_fs_entry_atime(get());
    }

    /**
        Returns the entry's creation time.
        @return the entry's creation time.
     */
    time_t getCreationTime() const {
        return al_get_fs_entry_ctime(get());
    }

    /**
        Returns the entry's last modification time.
        @return the entry's last modification time.
     */
    time_t getModificationTime() const {
        return al_get_fs_entry_mtime(get());
    }

    /**
        Returns the size of the file.
        @return the size of the file.
     */
    off_t getSize() const {
        return al_get_fs_entry_size(get());
    }

    /**
        Checks if the entry exists in the file system.
        @return true on success.
     */
    bool exists() const {
        return al_fs_entry_exists(get());
    }

    /**
        Updates the file status information.
        @return true on success.
     */
    bool update() {
        return al_update_fs_entry(get());
    }

    /**
        Deletes this file or empty directory from the filesystem.
        @return true on success.
     */
    bool remove() {
        return al_remove_fs_entry(get());
    }

    /**
        A class used for iterating entries of a directory.
     */
    class const_iterator : public std::iterator<std::forward_iterator_tag, FileEntry> {
    public:
        /**
            Returns the current file entry.
            @return the current file entry.
         */
        FileEntry operator *() const {
            return m_fileEntry;
        }

        /**
            Checks if two iterators point to the same file entry.
            @param it the other iterator.
            @return true if this and given iterator point to the same file entry, false otherwise.
         */
        bool operator == (const const_iterator &it) const {
            return m_fileEntry.get() == it.m_fileEntry.get();
        }

        /**
            Checks if two iterators point to a different file entry.
            @param it the other iterator.
            @return true if this and given iterator point to a different file entry.
         */
        bool operator != (const const_iterator &it) const {
            return !operator ==(it);
        }

        /**
            Increments the iterator to point to the next file entry.
            @return reference to this.
         */
        const_iterator &operator ++() {
            _readFileEntry();
            return *this;
        }

    private:
        //dir entry
        ALLEGRO_FS_ENTRY *m_dirEntry;

        //current file entry
        std::shared_ptr<ALLEGRO_FS_ENTRY> m_fileEntry;

        //internal constructor
        const_iterator(ALLEGRO_FS_ENTRY *dirEntry) : m_dirEntry(dirEntry) {
            if (al_open_directory(m_dirEntry)) _readFileEntry();
        }

        //empty iterator constructor
        const_iterator() : m_dirEntry(0) {
        }

        //read a file entry
        void _readFileEntry() {
            m_fileEntry = std::shared_ptr<ALLEGRO_FS_ENTRY>(al_read_directory(m_dirEntry), al_destroy_fs_entry);
        }

        friend class FileEntry;
    };

    /**
        Returns an iterator that points to the first file entry.
        @return an iterator that points to the first file entry.
     */
    const_iterator begin() const {
        return get();
    }

    /**
        Returns an iterator that points to the file entries end.
        @return an iterator that points to the file entries end.
     */
    const_iterator end() const {
        return const_iterator();
    }

    /**
        Constructor from allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    FileEntry(ALLEGRO_FS_ENTRY *object, bool managed = true) : Shared(object, managed, al_destroy_fs_entry) {
    }

private:
    //internal constructor from object pointer
    FileEntry(const std::shared_ptr<ALLEGRO_FS_ENTRY> &object) : Shared(object) {
    }

    friend class const_iterator;
};


} //namespace alx


#endif //ALX_FILEENTRY_HPP
