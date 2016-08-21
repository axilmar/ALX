#ifndef ALX_FILEPATH_HPP
#define ALX_FILEPATH_HPP


#include <allegro5/allegro.h>
#include "alx/Shared.hpp"
#include "alx/String.hpp"


namespace alx {


/**
    Shared-based wrapper class ALLEGRO_PATH.
 */
class FilePath : public Shared<ALLEGRO_PATH> {
public:
    /**
        Null constructor.
     */
    FilePath() {
    }

    /**
        Creates a path.
        @param path path string.
        @param dir if true, the path is created for a directory.
     */
    FilePath(const char *path, bool dir = false) : Shared(!dir ? al_create_path(path) : al_create_path_for_directory(path), al_destroy_path) {
    }

    /**
        Clones this path object.
        @return a clone of this object.
     */
    FilePath clone() const {
        return al_clone_path(get());
    }

    /**
        Converts the path to a string.
        @return a null-terminated string that represents the path.
     */
    operator String () const {
        return String(al_path_cstr(get(), ALLEGRO_NATIVE_PATH_SEP));
    }

    /**
        Returns the drive letter.
        @return the drive letter.
     */
    String getDrive() const {
        return String(al_get_path_drive(get()));
    }

    /**
        Returns the number of directory components this path has.
        @return the number of directory components this path has.
     */
    int getNumComponents() const {
        return al_get_path_num_components(get());
    }

    /**
        returns the path component at given index.
        @param index index.
        @return the path component.
     */
    String getComponent(int index) const {
        return al_get_path_component(get(), index);
    }

    /**
        Returns the last directory component.
        @return the last directory component.
     */
    String getTail() const {
        return String(al_get_path_tail(get()));
    }

    /**
        Returns the filename of the path.
        @return the filename of the path.
     */
    String getFilename() const {
        return String(al_get_path_filename(get()));
    }

    /**
        Returns the basename of the path.
        @return the basename of the path.
     */
    String getBasename() const {
        return String(al_get_path_basename(get()));
    }

    /**
        Returns the filename extension.
        @return the filename extension.
     */
    String getExtension() const {
        return String(al_get_path_extension(get()));
    }

    /**
        Returns the directory of the path,
        i.e. all components joined together using the native directory delimiter.
     */
    String getDirectory() const {
        String result = "";
        for(int i = 0; i < getNumComponents(); ++i) {
            result += getComponent(i);
            result += ALLEGRO_NATIVE_PATH_SEP;
        }
        return result;
    }

    /**
        Joins two paths.
        @param tail source path to append to this.
        @return true on success.
     */
    bool setTail(const FilePath &tail) {
        return al_join_paths(get(), tail.get());
    }

    /**
        Adds the given path as head of this path.
        @param head the head path.
        @return true on success.
     */
    bool setHead(const FilePath &head) {
        return al_rebase_path(head.get(), get());
    }

    /**
        Sets the drive.
        @param drive drive.
     */
    void setDrive(const char *drive) {
        al_set_path_drive(get(), drive);
    }

    /**
        Appends a path string.
        @param path string to append.
     */
    void addPath(const char *path) {
        al_append_path_component(get(), path);
    }

    /**
        Inserts a path string at the specific position.
        @param index index.
        @param path path string.
     */
    void insertPath(int index, const char *path) {
        al_insert_path_component(get(), index, path);
    }

    /**
        Replaces a path string at the specific position.
        @param index index.
        @param path path string.
     */
    void replacePath(int index, const char *path) {
        al_replace_path_component(get(), index, path);
    }

    /**
        Removes a path string at the specific position.
        @param index index of path component.
     */
    void removePath(int index) {
        al_remove_path_component(get(), index);
    }

    /**
        Removes the last path component.
     */
    void removeTail() {
        al_drop_path_tail(get());
    }

    /**
        Sets the filename.
        @param filename filename.
     */
    void setFilename(const char *filename) {
        al_set_path_filename(get(), filename);
    }

    /**
        Sets the extension.
        @param extension extension.
     */
    void setExtension(const char *extension) {
        al_set_path_extension(get(), extension);
    }

    /**
        Makes the path canonical.
        @return true on success.
     */
    bool setCanonical() {
        return al_make_path_canonical(get());
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    FilePath(ALLEGRO_PATH *object, bool managed = true) : Shared(object, managed, al_destroy_path) {
    }
};


} //namespace alx


#endif //ALX_FILEPATH_HPP
