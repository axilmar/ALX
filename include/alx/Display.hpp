#ifndef ALX_DISPLAY_HPP
#define ALX_DISPLAY_HPP


#include "alx/Bitmap.hpp"
#include "alx/Point.hpp"
#include "alx/Size.hpp"
#include "alx/EventSource.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_DISPLAY.
 */
class Display : public Shared<ALLEGRO_DISPLAY> {
public:
    /**
        Null constructor.
     */
    Display() {
    }

    /**
        creates a display from the given size.
        @param width width.
        @param height height.
     */
    Display(int width, int height) : Shared(al_create_display(width, height), al_destroy_display) {
    }

    /**
        Acknowledges the resize operation.
        @return true on success.
     */
    bool acknowledgeResize() {
        return al_acknowledge_resize(get());
    }

    /**
        Returns a bitmap object that represents the backbuffer.
        @return a bitmap object that represents the backbuffer.
     */
    Bitmap getBackbuffer() const {
        return Bitmap(al_get_backbuffer(get()), false);
    }

    /**
        Returns the flags of the display.
        @return the flags of the display.
     */
    int getFlags() const {
        return al_get_display_flags(get());
    }

    /**
        Returns the pixel format of the display.
        @return the pixel format of the display.
     */
    int getFormat() const {
        return al_get_display_format(get());
    }

    /**
        Returns the refresh rate of the display.
        @return the refresh rate of the display.
     */
    int getRefreshRate() const {
        return al_get_display_refresh_rate(get());
    }

    /**
        Returns the window position.
        @return the window position.
     */
    Point<int> getWindowPosition() const {
        int x, y;
        al_get_window_position(get(), &x, &y);
        return Point<int>(x, y);
    }

    /**
        Sets the window position.
        @param x horizontal position.
        @param y vertical position.
     */
    void setWindowPosition(int x, int y) {
        al_set_window_position(get(), x, y);
    }

    /**
        Sets the window position.
        @param pos position.
     */
    void setWindowPosition(const Point<int> &pos) {
        al_set_window_position(get(), pos.getX(), pos.getY());
    }

    /**
        Returns the width of the display.
        @return the width of the display.
     */
    int getWidth() const {
        return al_get_display_width(get());
    }

    /**
        Returns the height of the display.
        @return the height of the display.
     */
    int getHeight() const {
        return al_get_display_height(get());
    }

    /**
        Returns the size of the display.
        @return the size of the display.
     */
    Size<int> getSize() const {
        return Size<int>(getWidth(), getHeight());
    }

    /**
        Sets the size of the display.
        @param width width.
        @param height height.
        @return true on success.
     */
    bool setSize(int width, int height) {
        return al_resize_display(get(), width, height);
    }

    /**
        Sets the size of the display.
        @param size size.
        @return true on success.
     */
    bool setSize(const Size<int> &size) {
        return setSize(size.getWidth(), size.getHeight());
    }

    /**
        Sets the window icon.
        @param bitmap bitmap for the icon.
     */
    void setWindowIcon(const Bitmap &bitmap) {
        al_set_display_icon(get(), bitmap.get());
    }

    /**
        Retrieves an option.
        @param option option identifier.
        @return option value.
     */
    int getOption(int option) const {
        return al_get_display_option(get(), option);
    }

    /**
        Sets the title of the window.
        @param title title.
     */
    void setWindowTitle(const char *title) {
        al_set_window_title(get(), title);
    }

    /**
        Enables or disables a flag.
        @param flag flag to change.
        @param enabled true if enabled.
        @return true on success.
     */
    bool setFlagEnabled(int flag, bool enabled) {
        return al_toggle_display_flag(get(), flag, enabled);
    }

    /**
        Returns the event source of the display.
        @return the event source of the display.
     */
    EventSource getEventSource() const {
        return EventSource(al_get_display_event_source(get()), false);
    }

    /**
        Returns the event source of the display.
        @return the event source of the display.
     */
    operator EventSource() const {
        return getEventSource();
    }

    /**
        Sets the target bitmap to be the backbuffer of the given display.
        @param display display.
     */
    static void setTarget(Display &display) {
        al_set_target_backbuffer(display.get());
    }

    /**
        Returns the current display.
        @return the current display.
     */
    static Display getCurrent() {
        return Display(al_get_current_display(), false);
    }

    /**
        Sets the position of the mouse cursor.
        @param x x coordinate.
        @param y y coordinate.
     */
    void setMousePosition(int x, int y) {
        al_set_mouse_xy(get(), x, y);
    }

    /**
        Sets the position of the mouse cursor.
        @param pt mouse point.
     */
    void setMousePosition(const Point<int> &pt) {
        setMousePosition(pt.getX(), pt.getY());
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Display(ALLEGRO_DISPLAY *object, bool managed = true) : Shared(object, managed, al_destroy_display) {
    }
};


} //namespace alx


#endif //ALX_DISPLAY_HPP
