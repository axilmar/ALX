#ifndef ALX_RECT_HPP
#define ALX_RECT_HPP


#include <allegro5/allegro.h>
#include "Point.hpp"
#include "Size.hpp"


namespace alx {


/**
    A rectangle.
    @param T type of coordinate.
 */
template <class T> class Rect {
public:
    /**
        The default constructor.
        No member is initialized for performance reasons (for example, if resizing a large vector of rectangles).
     */
    Rect() {
    }

    /**
        Constructor from parameters.
        @param left left coordinate.
        @param top top coordinate
        @param right right coordinate.
        @param bottom bottom coordinate.
     */
    Rect(T left, T top, T right, T bottom) {
        set(left, top, right, bottom);
    }

    //TODO constructor from initializer list

    /**
        Constructor from point and size.
        @param topLeft top left point.
        @param size size.
     */
    Rect(const Point<T> &topLeft, const Size<T> &size) {
        set(topLeft, size);
    }

    /**
        Returns the left coordinate.
        @return the left coordinate.
     */
    T getLeft() const {
        return m_left;
    }

    /**
        Returns the top coordinate.
        @return the top coordinate.
     */
    T getTop() const {
        return m_top;
    }

    /**
        Returns the right coordinate.
        @return the right coordinate.
     */
    T getRight() const {
        return m_right;
    }

    /**
        Returns the bottom coordinate.
        @return the bottom coordinate.
     */
    T getBottom() const {
        return m_bottom;
    }

    /**
        Returns the width.
        @return the width.
     */
    T getWidth() const {
        return m_right - m_left + 1;
    }

    /**
        Returns the height.
        @return the height.
     */
    T getHeight() const {
        return m_bottom - m_top + 1;
    }

    /**
        Returns the horizontal center.
        @return the horizontal center.
     */
    T getCenterX() const {
        return m_left + getWidth() / 2;
    }

    /**
        Returns the vertical center.
        @return the vertical center.
     */
    T getCenterY() const {
        return m_top + getHeight() / 2;
    }

    //TODO test intersection functions

    //TODO is normal function

    //TODO assignment functions

    /**
        Sets the rectangles from individual parameters.
        @param left left coordinate.
        @param top top coordinate
        @param right right coordinate.
        @param bottom bottom coordinate.
     */
    void set(T left, T top, T right, T bottom) {
        m_left   = left;
        m_top    = top;
        m_right  = right;
        m_bottom = bottom;
    }

    //TODO individual coordinates set functions

    /**
        Set from from point and size.
        @param topLeft top left point.
        @param size size.
     */
    void set(const Point<T> &topLeft, const Size<T> &size) {
        m_left   = topLeft.getX();
        m_top    = topLeft.getY();
        m_right  = m_left + size.getWidth()  - 1;
        m_bottom = m_top  + size.getHeight() - 1;
    }

    //TODO move and offset functions

    //TODO union and intersection functions

    /**
        Returns the current bitmap clipping.
        @return A rectangle that contains the current clipping.
     */
    static Rect<T> getClipping() {
        int x, y, w, h;
        al_get_clipping_rectangle(&x, &y, &w, &h);
        return Rect<T>(Point<T>(x, y), Size<T>(w, h));
    }

    /**
        Sets the current clipping from this rectangle.
     */
    void setClipping() {
        al_set_clipping_rectangle(m_left, m_top, getWidth(), getHeight());
    }

private:
    T m_left;
    T m_top;
    T m_right;
    T m_bottom;
};


} //namespace alx


#endif //ALX_RECT_HPP
