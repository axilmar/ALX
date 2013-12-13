#ifndef ALX_NATIVEFILEDIALOG_HPP
#define ALX_NATIVEFILEDIALOG_HPP


#include <vector>
#include <allegro5/allegro_native_dialog.h>
#include "alx_Display.hpp"
#include "alx_FilePath.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_FILECHOOSER.
 */
class NativeFileDialog : public Shared<ALLEGRO_FILECHOOSER> {
public:
    /**
        Null constructor.
     */
    NativeFileDialog() {
    }

    /**
        Constructor.
        @param title the window title.
        @param path the initial path.
        @param patterns list of semicolon separated file patterns to match.
        @param mode mode.
     */
    NativeFileDialog(const char *title, const char *path, const char *patterns, int mode = 0) :
        Shared(al_create_native_file_dialog(path, title, patterns, mode), al_destroy_native_file_dialog)
    {
    }

    /**
        Returns the number of files selection.
        @return the number of files selection.
     */
    int getSelectedFileCount() const {
        return al_get_native_file_dialog_count(get());
    }

    /**
        Returns the path of the given selected file.
        @param index index of files.
        @return the path of the given selected file.
     */
    String getSelectedFile(int index) const {
        return String(al_get_native_file_dialog_path(get(), index), false);
    }

    /**
        Returns a vector with all selected file paths.
        @return a vector with all selected file paths.
     */
    std::vector<FilePath> getSelectedFilePaths() const {
        std::vector<FilePath> result;
        int count = getSelectedFileCount();
        for(int index = 0; index < count; ++index) {
            result.push_back(FilePath(getSelectedFile(index)));
        }
        return result;
    }

    /**
        Shows this dialog on the given display.
        @param display display to show the dialog onto.
        @return true on success.
     */
    bool show(Display &display) {
        return al_show_native_file_dialog(display.get(), get());
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    NativeFileDialog(ALLEGRO_FILECHOOSER *object, bool managed = true) :
        Shared(object, managed, al_destroy_native_file_dialog)
    {
    }
};


} //namespace alx


#endif //ALX_NATIVEFILEDIALOG_HPP
