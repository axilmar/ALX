#ifndef ALX_FILEPATH_HPP
#define ALX_FILEPATH_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


/**
    Value-based wrapper class ALLEGRO_PATH.
 */
class FilePath {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    FilePath(ALLEGRO_PATH *path, bool managed = true) : m_object(path, managed ? al_destroy_path : [](ALLEGRO_PATH *){}) {
    }

    /**
        Creates a path.
        @param path path string.
        @param dir if true, the path is created for a directory.
     */
    FilePath(const char *path, bool dir = false) : m_object(dir ? al_create_path(path) : al_create_path_for_directory(path), al_destroy_path) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Clones this path object.
        @return a clone of this object.
     */
    FilePath clone() const {
        return al_clone_path(m_object.get());
    }

    /**
        Converts the path to a string.
        @return a null-terminated string that represents the path.
     */
    operator const char *() const {
        return al_path_cstr(m_object.get(), ALLEGRO_NATIVE_PATH_SEP);
    }

    /**
        Returns the drive letter.
        @return the drive letter.
     */
    const char *getDrive() const {
        return al_get_path_drive(m_object.get());
    }

    /**
        Returns the number of directory components this path has.
        @return the number of directory components this path has.
     */
    int getNumComponents() const {
        return al_get_path_num_components(m_object.get());
    }

    /**
        returns the path component at given index.
        @param index index.
        @return the path component.
     */
    const char *getComponent(int index) const {
        return al_get_path_component(m_object.get(), index);
    }

    /**
        Returns the last directory component.
        @return the last directory component.
     */
    const char *getTail() const {
        return al_get_path_tail(m_object.get());
    }

    /**
        Returns the filename of the path.
        @return the filename of the path.
     */
    const char *getFilename() const {
        return al_get_path_filename(m_object.get());
    }

    /**
        Returns the basename of the path.
        @return the basename of the path.
     */
    const char *getBasename() const {
        return al_get_path_basename(m_object.get());
    }

    /**
        Returns the filename extension.
        @return the filename extension.
     */
    const char *getExtension() const {
        return al_get_path_extension(m_object.get());
    }

    /**
        Joins two paths.
        @param tail source path to append to this.
        @return true on success.
     */
    bool setTail(const FilePath &tail) {
        return al_join_paths(m_object.get(), tail.m_object.get());
    }

    /**
        Adds the given path as head of this path.
        @param head the head path.
        @return true on success.
     */
    bool setHead(const FilePath &head) {
        return al_rebase_path(head.m_object.get(), m_object.get());    
    }

    /**
        Sets the drive.
        @param drive drive.
     */
    void setDrive(const char *drive) {
        al_set_path_drive(m_object.get(), drive);
    }

    /**
        Appends a path string.
        @param path string to append.
     */
    void addPath(const char *path) {
        al_append_path_component(m_object.get(), path);
    }

    /**
        Inserts a path string at the specific position.
        @param index index.
        @param path path string.
     */
    void insertPath(int index, const char *path) {
        al_insert_path_component(m_object.get(), index, path);
    }

    /**
        Replaces a path string at the specific position.
        @param index index.
        @param path path string.
     */
    void replacePath(int index, const char *path) {
        al_replace_path_component(m_object.get(), index, path);
    }

    /**
        Removes a path string at the specific position.
        @param path path string.
     */
    void removePath(int index) {
        al_remove_path_component(m_object.get(), index);
    }

    /**
        Removes the last path component.
     */
    void removeTail() {
        al_drop_path_tail(m_object.get());
    }

    /**
        Sets the filename.
        @param filename filename. 
     */
    void setFilename(const char *filename) {
        al_set_path_filename(m_object.get(), filename);
    }

    /**
        Sets the extension.
        @param extension extension.
     */
    void setExtension(const char *extension) {
        al_set_path_extension(m_object.get(), extension);
    }

    /**
        Makes the path canonical.
        @return true on success.
     */
    bool setCanonical() {
        al_make_path_canonical(m_object.get());
    }

private:
    std::shared_ptr<ALLEGRO_PATH> m_object;
};


} //namespace alx


#endif //ALX_FILEPATH_HPP
