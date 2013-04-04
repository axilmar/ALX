#ifndef ALX_BITMAP_HPP
#define ALX_BITMAP_HPP


#include <memory>
#include <allegro5/allegro.h>
#include "Point.hpp"
#include "Size.hpp"
#include "File.hpp"


namespace alx {


//TODO


/**
    Value-based wrapper around ALLEGRO_BITMAP.
 */
class Bitmap {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Bitmap(ALLEGRO_BITMAP *object, bool managed = true) : m_object(object, managed ? al_destroy_bitmap : [](ALLEGRO_BITMAP *){}) {
    }

    /**
        Creates a bitmap of the specific size.
        @param width width.
        @param height height.
     */
    Bitmap(int width, int height) : m_object(al_create_bitmap(width, height), al_destroy_bitmap) {
    }

    /**
        Creates a subbitmap.
        @param parent parent bitmap.
        @param x x.
        @param y y.
        @param width width.
        @param height height.
     */
    Bitmap(Bitmap &parent, int x, int y, int width, int height) : m_object(al_create_sub_bitmap(parent.m_object.get(), x, y, width, height), al_destroy_bitmap) {
    }

    /**
        Loads a bitmap from file.
        @param filename filename.
     */
    Bitmap(const char *filename) : m_object(al_load_bitmap(filename), al_destroy_bitmap) {
    }

    /**
        Loads a bitmap from file.
        @param file file.
        @param ext filename extension.
     */
    Bitmap(const File &file, const char *ext) : m_object(al_load_bitmap_f(file.m_object.get(), ext), al_destroy_bitmap) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Clones this bitmap.
        @return a copy of this bitmap.
     */
    Bitmap clone() const {
        return al_clone_bitmap(m_object.get());
    }

    /**
        Returns the bitmap's flags.
        @return the bitmap's flags.
     */
    int getFlags() const {
        return al_get_bitmap_flags(m_object.get());
    }

    /**
        Returns the bitmap's format.
        @return the bitmap's format.
     */
    int getFormat() const {
        return al_get_bitmap_format(m_object.get());
    }

    /**
        Returns the bitmap's width.
        @return the bitmap's width.
     */
    int getWidth() const {
        return al_get_bitmap_width(m_object.get());
    }

    /**
        Returns the bitmap's height.
        @return the bitmap's height.
     */
    int getHeight() const {
        return al_get_bitmap_height(m_object.get());
    }

    /**
        Returns the bitmap's size.
        @return the bitmap's size.
     */
    Size<int> getSize() const {
        return Size<int>(al_get_bitmap_width(m_object.get()), al_get_bitmap_height(m_object.get()));
    }

    /**
        Returns a pixel.
        @param x x coordinate.
        @param y y coordinate.
        @return the color at the given coordinates.
     */
    ALLEGRO_COLOR getPixel(int x, int y) const {
        return al_get_pixel(m_object.get(), x, y);
    }

    /**
        Returns a pixel.
        @param pt point.
        @return the color at the given coordinates.
     */
    template <class T> ALLEGRO_COLOR getPixel(const Point<T> &pt) const {
        return al_get_pixel(m_object.get(), pt.x, pt.y);
    }

    /**
        Checks if the bitmap is locked.
        @return true if locked. 
     */
    bool isLocked() const {
        return al_is_bitmap_locked(m_object.get());
    }

    /**
        Checks if a bitmap is compatible with the given display.
        @return true if compatible.
     */
    bool isCompatible() const {
        return al_is_compatible_bitmap(m_object.get());
    }

    /**
        Checks if this bitmap is a subbitmap.
        @return true if subbitmap.
     */
    bool isSubBitmap() const {
        return al_is_sub_bitmap(m_object.get());
    }

    /**
        Locks the entire bitmap.
        @param format pixel format.
        @param flags flags.
        @return the locked region structure (according to the docs and examples, it does not need to be freed).
     */
    ALLEGRO_LOCKED_REGION *lock(int format, int flags) {
        return al_lock_bitmap(m_object.get(), format, flags);
    }

    /**
        Locks part of the bitmap.
        @param x horizontal coordinate.
        @param y vertical coordinate.
        @param width width.
        @param height height.
        @param format pixel format.
        @param flags flags.
        @return the locked region structure (according to the docs and examples, it does not need to be freed).
     */
    ALLEGRO_LOCKED_REGION *lock(int x, int y, int width, int height, int format, int flags) {
        return al_lock_bitmap_region(m_object.get(), x, y, width, height, format, flags);
    }

    /**
        Unlocks the bitmap.
        Usually, it needs
     */
    void unlock() {
        al_unlock_bitmap(m_object.get());
    }

    /**
        Class used for locking/unlocking a bitmap using RAII.
     */
    class Lock {
    public:
        /**
            Locks an entire bitmap.
            @param bitmap bitmap to lock.
            @param format pixel format.
            @param flags flags.
         */
        Lock(Bitmap &bitmap, int format, int flags) : m_bitmap(bitmap) {
            m_region = m_bitmap.lock(format, flags);
        }

        /**
            Locks part of the bitmap.
            @param x horizontal coordinate.
            @param y vertical coordinate.
            @param width width.
            @param height height.
            @param bitmap bitmap to lock.
            @param format pixel format.
            @param flags flags.
         */
        Lock(Bitmap &bitmap, int x, int y, int width, int height, int format, int flags) : m_bitmap(bitmap) {
            m_region = m_bitmap.lock(x, y, width, height, format, flags);
        }

        /**
            Unlocks the bitmap.
         */
        ~Lock() {
            m_bitmap.unlock();
        }

        /**
            Returns the bitmap's locked region.
            @return the bitmap's locked region.
         */
        ALLEGRO_LOCKED_REGION *getLockedRegion() const {
            return m_region;
        }

    private:
        Bitmap &m_bitmap;
        ALLEGRO_LOCKED_REGION *m_region;
    };

    /**
        Draws this bitmap onto the target bitmap.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param flags flags.
     */
    void draw(float dx, float dy, int flags = 0) const {
        al_draw_bitmap(m_object.get(), dx, dy, flags);
    }

    /**
        Draws part of this bitmap onto the target bitmap.
        @param sx source x position.
        @param sy source y position.
        @param sw source width.
        @param sh source height.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param flags flags.
     */
    void draw(float sx, float sy, float sw, float sh, float dx, float dy, int flags = 0) const {
        al_draw_bitmap_region(m_object.get(), sx, sy, sw, sh, dx, dy, flags);
    }

    /**
        Draws this bitmap onto the target bitmap tinted by the given color.
        @param color color.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param flags flags.
     */
    void drawTinted(const ALLEGRO_COLOR &color, float dx, float dy, int flags = 0) const {
        al_draw_tinted_bitmap(m_object.get(), color, dx, dy, flags);
    }

    /**
        Draws part of this bitmap onto the target bitmap tinted by the given color.
        @param color color.
        @param sx source x position.
        @param sy source y position.
        @param sw source width.
        @param sh source height.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param flags flags.
     */
    void drawTinted(const ALLEGRO_COLOR &color, float sx, float sy, float sw, float sh, float dx, float dy, int flags = 0) const {
        al_draw_tinted_bitmap_region(m_object.get(), color, sx, sy, sw, sh, dx, dy, flags);
    }

    /**
        Draws a rotated bitmap.
        @param cx center x.
        @param cy center y.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param angle angle in radians; clockwise.
        @param flags flags.
     */
    void drawRotated(float cx, float cy, float dx, float dy, float angle, int flags = 0) {
        al_draw_rotated_bitmap(m_object.get(), cx, cy, dx, dy, angle, flags);
    }

    /**
        Draws a tinted rotated bitmap.
        @param color color.
        @param cx center x.
        @param cy center y.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param angle angle in radians; clockwise.
        @param flags flags.
     */
    void drawTintedRotated(const ALLEGRO_COLOR &color, float cx, float cy, float dx, float dy, float angle, int flags = 0) {
        al_draw_tinted_rotated_bitmap(m_object.get(), color, cx, cy, dx, dy, angle, flags);
    }

    /**
        Draws a scaled and rotated bitmap.
        @param cx center x.
        @param cy center y.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param xscale scale along the x axis.
        @param yscale scale along the y axis.
        @param angle angle in radians; clockwise.
        @param flags flags.
     */
    void drawScaledRotated(float cx, float cy, float dx, float dy, float xscale, float yscale, float angle, int flags = 0) {
        al_draw_scaled_rotated_bitmap(m_object.get(), cx, cy, dx, dy, xscale, yscale, angle, flags);
    }

    /**
        Draws a tinted, scaled and rotated bitmap.
        @param color color.
        @param cx center x.
        @param cy center y.
        @param dx target horizontal position.
        @param dy target vertical position.
        @param xscale scale along the x axis.
        @param yscale scale along the y axis.
        @param angle angle in radians; clockwise.
        @param flags flags.
     */
    void drawScaledRotated(const ALLEGRO_COLOR &color, float cx, float cy, float dx, float dy, float xscale, float yscale, float angle, int flags = 0) {
        al_draw_tinted_scaled_rotated_bitmap(m_object.get(), color, cx, cy, dx, dy, xscale, yscale, angle, flags);
    }

    /**
        Draws a scaled bitmap.
        @param sx source x.
        @param sy source y.
        @param sw source width.
        @param sh source height.
        @param dx destination x.
        @param dy destination y.
        @param dw destination width.
        @param dh destination height.
        @param flags same as for al_draw_bitmap.
     */
    void drawScaled(float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, int flags = 0) {
        al_draw_scaled_bitmap(m_object.get(), sx, sy, sw, sh, dx, dy, dw, dh, flags);
    }

    /**
        Draws a tinted scaled bitmap.
        @param color color.
        @param sx source x.
        @param sy source y.
        @param sw source width.
        @param sh source height.
        @param dx destination x.
        @param dy destination y.
        @param dw destination width.
        @param dh destination height.
        @param flags same as for al_draw_bitmap.
     */
    void drawTintedScaled(const ALLEGRO_COLOR &color, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, int flags = 0) {
        al_draw_tinted_scaled_bitmap(m_object.get(), color, sx, sy, sw, sh, dx, dy, dw, dh, flags);
    }

    /**
        Returns the target bitmap.
     */
    static Bitmap getTarget() {
        return Bitmap(al_get_target_bitmap(), false);
    }

    /**
        Sets the target bitmap.
        @param bmp the target bitmap.
     */
    static void setTarget(Bitmap &bmp) {
        al_set_target_bitmap(bmp.m_object.get());
    }

    /**
        Converts mask to alpha.
        @param color color.
     */
    void convertMaskToAlpha(const ALLEGRO_COLOR &color) {
        al_convert_mask_to_alpha(m_object.get(), color);
    }

    /**
        Helper class used for holding drawing using RAII.
     */
    class HoldDrawing {
    public:
        /**
            Enables hold drawing.
         */
        HoldDrawing() {
            al_hold_bitmap_drawing(true);
        }

        /**
            Disables hold drawing.
         */
        ~HoldDrawing() {
            al_hold_bitmap_drawing(false);
        }
    };

    /**
        loads a bitmap from a file.
        @param filename filename.
     */
    bool load(const char *filename) {
        m_object = std::shared_ptr<ALLEGRO_BITMAP>(al_load_bitmap(filename), al_destroy_bitmap);
        return !isNull();
    }

    /**
        loads a bitmap from a file.
        @param file file.
        @param ext filename extension.
     */
    bool load(const File &file, const char *ext) {
        m_object = std::shared_ptr<ALLEGRO_BITMAP>(al_load_bitmap_f(file.m_object.get(), ext), al_destroy_bitmap);
        return !isNull();
    }

    /**
        Saves a bitmap.
        @param filename filename.
        @return true on success.
     */
    bool save(const char *filename) const {
        return al_save_bitmap(filename, m_object.get());
    }

    /**
        Saves a bitmap.
        @param file file.
        @param ext filename extension.
        @return true on success.
     */
    bool save(const File &file, const char *ext) const {
        return al_save_bitmap_f(file.m_object.get(), ext, m_object.get());
    }

private:
    //allegro object
    std::shared_ptr<ALLEGRO_BITMAP> m_object;

    friend class Display;
};


} //namespace alx


#endif //ALX_BITMAP_HPP