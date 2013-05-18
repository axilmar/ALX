#ifndef ALX_FONT_HPP
#define ALX_FONT_HPP


#include <vector>
#include <tuple>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "String.hpp"
#include "Rect.hpp"
#include "Bitmap.hpp"
#include "File.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_FONT.
 */
class Font : public Shared<ALLEGRO_FONT> {
public:
    /**
        Null constructor.
     */
    Font() {
    }

    /**
        Constructor from file.
        @param filename name of file.
        @param size size in points.
        @param flags font flags.
     */
    Font(const char *filename, int size, int flags = 0) :
        Shared(al_load_font(filename, size, flags), al_destroy_font)
    {
    }

    /**
        TTF font constructor from file.
        @param file file.
        @param size size in points.
        @param flags font flags.
     */
    Font(const File &file, int size, int flags = 0) :
        Shared(al_load_ttf_font_f(file.get(), nullptr, size, flags), al_destroy_font)
    {
    }

    /**
        TTF font constructor from file.
        @param file file.
        @param filename used for additional files.
        @param size size in points.
        @param flags font flags.
     */
    Font(const File &file, const char *filename, int size, int flags = 0) :
        Shared(al_load_ttf_font_f(file.get(), filename, size, flags), al_destroy_font)
    {
    }

    /**
        Bitmap font constructor from file.
        @param filename name of file.
     */
    Font(const char *filename) :
        Shared(al_load_bitmap_font(filename), al_destroy_font)
    {
    }

    /**
        Creates a font from a bitmap.
        @param bmp bitmap.
        @param ranges ranges.
     */
    Font(const Bitmap &bmp, const std::vector<std::tuple<int, int>> &ranges) {
        grab(bmp, ranges);
    }

    /**
        Returns the pixel width of the given string for this font.
        @param str null-terminated string.
        @return pixel width of the given text.
     */
    int getWidth(const char *str) const {
        return al_get_text_width(get(), str);
    }

    /**
        Returns the pixel width of the given string for this font.
        @param str string.
        @return pixel width of the given text.
     */
    int getWidth(const String &str) const {
        return al_get_ustr_width(get(), str.get());
    }

    /**
        Returns the total height of the font.
        @return the font's height.
     */
    int getHeight() const {
        return al_get_font_line_height(get());
    }

    /**
        Returns the font ascent.
        @return the font ascent.
     */
    int getAscent() const {
        return al_get_font_ascent(get());
    }

    /**
        Returns the font descent.
        @return the font descent.
     */
    int getDescent() const {
        return al_get_font_descent(get());
    }

    /**
        Retrieves the actual dimensions of text.
        @param text text.
        @return dimensions.
     */
    Rect<int> getDimensions(const char *text) const {
        int x, y, w, h;
        al_get_text_dimensions(get(), text, &x, &y, &w, &h);
        return makeRect(makePoint(x, y), makeSize(w, h));
    }

    /**
        Retrieves the actual dimensions of text.
        @param text text.
        @return dimensions.
     */
    Rect<int> getDimensions(const String &text) const {
        int x, y, w, h;
        al_get_ustr_dimensions(get(), text.get(), &x, &y, &w, &h);
        return makeRect(makePoint(x, y), makeSize(w, h));
    }

    /**
        Draws text using this font.
        @param x target x coordinate.
        @param y target y coordinate.
        @param flags flags.
        @param color color.
        @param text null-terminated string to draw.
     */
    void draw(float x, float y, int flags, ALLEGRO_COLOR color, const char *text) const {
        al_draw_text(get(), color, x, y, flags, text);
    }

    /**
        Draws text using this font, with flags = 0.
        @param x target x coordinate.
        @param y target y coordinate.
        @param color color.
        @param text null-terminated string to draw.
     */
    void draw(float x, float y, ALLEGRO_COLOR color, const char *text) const {
        draw(x, y, 0, color, text);
    }

    /**
        Draws text using this font.
        @param x target x coordinate.
        @param y target y coordinate.
        @param flags flags.
        @param color color.
        @param text string to draw.
     */
    void draw(float x, float y, int flags, ALLEGRO_COLOR color, const String &text) const {
        al_draw_ustr(get(), color, x, y, flags, text.get());
    }

    /**
        Draws text using this font, with flags = 0.
        @param x target x coordinate.
        @param y target y coordinate.
        @param color color.
        @param text string to draw.
     */
    void draw(float x, float y, ALLEGRO_COLOR color, const String &text) const {
        draw(x, y, 0, color, text);
    }

    /**
        Printf-style draw.
        @param x target x coordinate.
        @param y target y coordinate.
        @param flags flags.
        @param color color.
        @param format printf-style format.
        @param ... printf-style arguments.
     */
    void drawf(float x, float y, int flags, ALLEGRO_COLOR color, const char *format, ...) const {
        va_list args;
        va_start(args, format);
        drawf(x, y, flags, color, format, args);
        va_end(args);
    }

    /**
        Printf-style draw with flags = 0.
        @param x target x coordinate.
        @param y target y coordinate.
        @param color color.
        @param format printf-style format.
        @param ... printf-style arguments.
     */
    void drawf(float x, float y, ALLEGRO_COLOR color, const char *format, ...) const {
        va_list args;
        va_start(args, format);
        drawf(x, y, 0, color, format, args);
        va_end(args);
    }

    /**
        Printf-style draw.
        @param x target x coordinate.
        @param y target y coordinate.
        @param flags flags.
        @param color color.
        @param format printf-style format.
        @param args arguments.
     */
    void drawf(float x, float y, int flags, ALLEGRO_COLOR color, const char *format, va_list args) const {
        String str;
        if (!str.printf(format, args)) str = "printf error";
        draw(x, y, flags, color, str);
    }

    /**
        Printf-style draw with flags = 0.
        @param x target x coordinate.
        @param y target y coordinate.
        @param color color.
        @param format printf-style format.
        @param args arguments.
     */
    void drawf(float x, float y, ALLEGRO_COLOR color, const char *format, va_list args) const {
        drawf(x, y, 0, color, format, args);
    }

    /**
        loads the font from a file.
        @param filename name of file.
        @param size size in points.
        @param flags font flags.
        @return true on success.
     */
    bool load(const char *filename, int size, int flags = 0) {
        reset(al_load_font(filename, size, flags), al_destroy_font);
        return (bool)(*this);
    }

    /**
        loads a true-type font from a file.
        @param file file to load the font from.
        @param size size in points.
        @param flags font flags.
        @return true on success.
     */
    bool load(const File &file, int size, int flags = 0) {
        reset(al_load_ttf_font_f(file.get(), nullptr, size, flags), al_destroy_font);
        return (bool)(*this);
    }

    /**
        loads a true-type font from a file.
        @param file file to load the font from.
        @param filename used for additional files.
        @param size size in points.
        @param flags font flags.
        @return true on success.
     */
    bool load(const File &file, const char *filename, int size, int flags = 0) {
        reset(al_load_ttf_font_f(file.get(), filename, size, flags), al_destroy_font);
        return (bool)(*this);
    }

    /**
        Creates a font from a bitmap.
        @param bmp bitmap.
        @param ranges ranges.
        @return true on success.
     */
    bool grab(const Bitmap &bmp, const std::vector<std::tuple<int, int>> &ranges) {
        std::vector<int> rangeBuffer;
        for(auto t : ranges) {
            rangeBuffer.push_back(std::get<0>(t));
            rangeBuffer.push_back(std::get<1>(t));
        }
        reset(al_grab_font_from_bitmap(bmp.get(), rangeBuffer.size(), rangeBuffer.data()), al_destroy_font);
        return (bool)(*this);
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Font(ALLEGRO_FONT *object, bool managed = true) :
        Shared(object, managed, al_destroy_font)
    {
    }
};


} //namespace alx


#endif //ALX_FONT_HPP
