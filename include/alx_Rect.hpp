#ifndef ALX_RECT_HPP
#define ALX_RECT_HPP


#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <allegro5/allegro.h>
#include "alx_Point.hpp"
#include "alx_Size.hpp"


#ifdef min
#undef min
#endif


#ifdef max
#undef max
#endif


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

    /**
        Constructor from initializer list.
        @param coords coordinates; only the 1st 4 values are used.
     */
    Rect(std::initializer_list<T> coords) {
        operator = (coords);
    }

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
        Returns the top-left coordinates of the rectangle.
     */
    Point<T> getTopLeft() const {
        return Point<T>(m_left, m_top);
    }

    /**
        Returns the top-right coordinates of the rectangle.
     */
    Point<T> getTopRight() const {
        return Point<T>(m_right, m_top);
    }

    /**
        Returns the bottom-left coordinates of the rectangle.
     */
    Point<T> getBottomLeft() const {
        return Point<T>(m_left, m_bottom);
    }

    /**
        Returns the bottom-right coordinates of the rectangle.
     */
    Point<T> getBottomRight() const {
        return Point<T>(m_right, m_bottom);
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
        Returns the size of the rectangle.
     */
    Size<T> getSize() const {
        return Size<T>(getWidth(), getHeight());
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

    /**
        Returns the rectangle's center.
        @return the rectangle's center.
     */
    Point<T> getCenter() const {
        return Point<T>(getCenterX(), getCenterY());
    }

    /**
        Checks intersection with point.
        @param x horizontal coordinate.
        @param y vertical coordinate.
        @return true if coordinates within the rectangle.
     */
    bool intersects(T x, T y) const {
        return x >= m_left && x <= m_right && y >= m_top && y <= m_bottom;
    }

    /**
        Checks intersection with point object.
        @param pt point object.
        @return true if coordinates within the rectangle.
     */
    bool intersects(const Point<T> &pt) const {
        return intersects(pt.getX(), pt.getY());
    }

    /**
        Checks intersection with rectangle.
        @param left left coordinate of rectangle.
        @param top top coordinate of rectangle.
        @param right right coordinate of rectangle.
        @param bottom bottom coordinate of rectangle.
        @return true if the two rectangles intersect, false otherwise.
     */
    bool intersects(T left, T top, T right, T bottom) const {
        return left <= m_right && right >= m_left && top <= m_bottom && bottom >= m_top;
    }

    /**
        Checks intersection with rectangle object.
        @param r rectangle.
        @return true if the two rectangles intersect, false otherwise.
     */
    bool intersects(const Rect<T> &r) const {
        return intersects(r.m_left, r.m_top, r.m_right, r.m_bottom);
    }

    /**
        Checks if left <= right and top <= bottom.
        @return true if normalized.
     */
    bool isNormalized() const {
        return m_left <= m_right && m_top <= m_bottom;
    }

    /**
        Checks if this and given rectangle are equal.
     */
    bool operator == (const Rect<T> &rct) const {
        return m_left == rct.m_left && m_top == rct.m_top && m_right == rct.m_right && m_bottom == rct.m_bottom;
    }

    /**
        Checks if this and given rectangle are different.
     */
    bool operator != (const Rect<T> &rct) const {
        return !operator == (rct);
    }

    /**
        sets the rectangle from coordinates.
        Only the first 4 coordinates are used.
        @param coords list of coordinates (left, top, right, bottom).
        @return reference to this.
     */
    Rect<T> &operator = (const std::initializer_list<T> &coords) {
        typename std::initializer_list<T>::const_iterator it = coords.begin();
        switch (coords.size()) {
            case 4: m_bottom = *(it + 3);
            case 3: m_right  = *(it + 2);
            case 2: m_top    = *(it + 1);
            case 1: m_left   = *it;
        }
        return *this;
    }

    /**
        Sets the left coordinate.
        @param x coordinate.
     */
    void setLeft(T x) {
        m_left = x;
    }

    /**
        Sets the top coordinate.
        @param y coordinate.
     */
    void setTop(T y) {
        m_top = y;
    }

    /**
        Sets the right coordinate.
        @param x coordinate.
     */
    void setRight(T x) {
        m_right = x;
    }

    /**
        Sets the bottom coordinate.
        @param y coordinate.
     */
    void setBottom(T y) {
        m_bottom = y;
    }

    /**
        sets the left and top coordinates.
        @param x left.
        @param y top.
     */
    void setTopLeft(T x, T y) {
        setLeft(x);
        setTop(y);
    }

    /**
        sets the left and top coordinates.
        @param pt coordinates.
     */
    void setTopLeft(const Point<T> &pt) {
        setTopLeft(pt.getX(), pt.getY());
    }

    /**
        sets the right and top coordinates.
        @param x right.
        @param y top.
     */
    void setTopRight(T x, T y) {
        setRight(x);
        setTop(y);
    }

    /**
        sets the right and top coordinates.
        @param pt coordinates.
     */
    void setTopRight(const Point<T> &pt) {
        setTopRight(pt.getX(), pt.getY());
    }

    /**
        sets the left and bottom coordinates.
        @param x left.
        @param y bottom.
     */
    void setBottomLeft(T x, T y) {
        setLeft(x);
        setBottom(y);
    }

    /**
        sets the left and bottom coordinates.
        @param pt coordinates.
     */
    void setBottomLeft(const Point<T> &pt) {
        setBottomLeft(pt.getX(), pt.getY());
    }

    /**
        sets the right and bottom coordinates.
        @param x right.
        @param y bottom.
     */
    void setBottomRight(T x, T y) {
        setright(x);
        setbottom(y);
    }

    /**
        sets the right and bottom coordinates.
        @param pt coordinates.
     */
    void setBottomRight(const Point<T> &pt) {
        setBottomRight(pt.getX(), pt.getY());
    }

    /**
        sets the width.
        @param w width.
     */
    void setWidth(T w) {
        m_right = m_left + w - 1;
    }

    /**
        sets the height.
        @param h height.
     */
    void setHeight(T h) {
        m_bottom = m_top + h - 1;
    }

    /**
        Sets the size of the rectangle.
        @param w width.
        @param h height.
     */
    void setSize(T w, T h) {
        setWidth(w);
        setHeight(h);
    }

    /**
        sets the size of the rectangle.
        @param sz size.
     */
    void setSize(const Size<T> &sz) {
        setSize(sz.getWidth(), sz.getHeight());
    }

    /**
        Moves the rectangle horizontally so as that the given coordinate is the center.
        @param cx new center x.
     */
    void setCenterX(T cx) {
        T w = getWidth();
        m_left  = cx - w/2;
        m_right = m_left + w - 1;
    }

    /**
        Moves the rectangle vertically so as that the given coordinate is the center.
        @param cy new center y.
     */
    void setCenterY(T cy) {
        T h = getHeight();
        m_top    = cy - h/2;
        m_bottom = m_top + h - 1;
    }

    /**
        Sets the center of the rectangle.
        @param cx horizontal center coordinate.
        @param cy vertical center coordinate.
     */
    void setCenter(T cx, T cy) {
        setCenterX(cx);
        setCenterY(cy);
    }

    /**
        sets the center of the rectangle from point.
        @param cpt center point.
     */
    void setCenter(const Point<T> &cpt) {
        setCenter(cpt.getX(), cpt.getY());
    }

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

    /**
        Moves the rectangle horizontally to the given left position.
        @param x new left position.
     */
    void moveToX(T x) {
        T w = getWidth();
        m_left = x;
        m_right = m_left + w - 1;
    }

    /**
        Moves the rectangle vertically to the given top position.
        @param y new top position.
     */
    void moveToY(T y) {
        T h = getHeight();
        m_top = y;
        m_bottom = m_top + h - 1;
    }

    /**
        moves the rectangle to the given top-left position.
        @param x new left position.
        @param y new top position.
     */
    void moveTo(T x, T y) {
        moveToX(x);
        moveToY(y);
    }

    /**
        Moves the rectangle to the given top-left position.
        @param pt new top-left position.
     */
    void moveTo(const Point<T> &pt) {
        moveToX(pt.getX());
        moveToY(pt.getY());
    }

    /**
        Copy this into another rect with the given x position.
     */
    Rect<T> moveToX(T x) const {
        return Rect<T>(Point<T>(x, getTop()), getSize());
    }

    /**
        Copy this into another rect with the given y position.
     */
    Rect<T> moveToY(T y) const {
        return Rect<T>(Point<T>(getLeft(), y), getSize());
    }

    /**
        Copy this into another rect with the given x, y position.
     */
    Rect<T> moveTo(T x, T y) const {
        return Rect<T>(Point<T>(x, y), getSize());
    }

    /**
        Copy this into another rect with the given x, y position.
     */
    Rect<T> moveTo(const Point<T> &pt) const {
        return Rect<T>(pt, getSize());
    }

    /**
        Moves the rectangle horizontally by the given points.
        @param dx horizontal delta.
     */
    void offsetByX(T dx) {
        T w = getWidth();
        m_left += dx;
        m_right = m_left + w - 1;
    }

    /**
        Moves the rectangle vertically by the given points.
        @param dy vertical delta.
     */
    void offsetByY(T dy) {
        T h = getHeight();
        m_top += dy;
        m_bottom = m_top + h - 1;
    }

    /**
        Moves the rectangle by the given amount.
        @param dx horizontal delta.
        @param dy vertical delta.
     */
    void offsetBy(T dx, T dy) {
        offsetByX(dx);
        offsetByY(dy);
    }

    /**
        Moves the rectangle by the given amount.
        @param dpt delta point.
     */
    void offsetBy(const Point<T> &dpt) {
        offsetBy(dpt.getX(), dpt.getY());
    }

    /**
        Moves the rectangle by the given amount.
        @param dsz delta size.
     */
    void offsetBy(const Size<T> &dsz) {
        offsetBy(dsz.getWidth(), dsz.getHeight());
    }

    /**
        Offsets a copy of this rectangle horizontally.
     */
    Rect<T> offsetByX(T dx) const {
        return Rect<T>(Point<T>(getLeft() + dx, getTop()), getSize());
    }

    /**
        Offsets a copy of this rectangle vertically.
     */
    Rect<T> offsetByY(T dy) const {
        return Rect<T>(Point<T>(getLeft(), getTop() + dy), getSize());
    }

    /**
        Offsets a copy of this rectangle.
     */
    Rect<T> offsetBy(T dx, T dy) const {
        return Rect<T>(Point<T>(getLeft() + dx, getTop() + dy), getSize());
    }

    /**
        Offsets a copy of this rectangle.
     */
    Rect<T> offsetBy(const Point<T> &dpt) const {
        return offsetBy(dpt.getX(), dpt.getY());
    }

    /**
        Calculates the intersection of two rectangles.
        @param a first rectangle.
        @param b second rectangle.
        @return the rectangle intersection.
     */
    friend Rect<T> operator & (const Rect<T> &a, const Rect<T> &b) {
        return Rect<T>(
            std::max(a.m_left  , b.m_left  ),
            std::max(a.m_top   , b.m_top   ),
            std::min(a.m_right , b.m_right ),
            std::min(a.m_bottom, b.m_bottom));
    }

    /**
        calculates the intersection of this and given rectangle and stores the result in this.
        @param rt the other rectangle.
        @return reference to this.
     */
    Rect<T> &operator &= (const Rect<T> &rt) {
        m_left   = std::max(m_left  , rt.m_left  );
        m_top    = std::max(m_top   , rt.m_top   );
        m_right  = std::min(m_right , rt.m_right );
        m_bottom = std::min(m_bottom, rt.m_bottom);
        return *this;
    }

    /**
        Calculates the union of two rectangles.
        @param a first rectangle.
        @param b second rectangle.
        @return the rectangle union.
     */
    friend Rect<T> operator | (const Rect<T> &a, const Rect<T> &b) {
        return Rect<T>(
            std::min(a.m_left  , b.m_left  ),
            std::min(a.m_top   , b.m_top   ),
            std::max(a.m_right , b.m_right ),
            std::max(a.m_bottom, b.m_bottom));
    }

    /**
        calculates the union of this and given rectangle and stores the result in this.
        @param rt the other rectangle.
        @return reference to this.
     */
    Rect<T> &operator |= (const Rect<T> &rt) {
        m_left   = std::min(m_left  , rt.m_left  );
        m_top    = std::min(m_top   , rt.m_top   );
        m_right  = std::max(m_right , rt.m_right );
        m_bottom = std::max(m_bottom, rt.m_bottom);
        return *this;
    }

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
    void setClipping() const {
        al_set_clipping_rectangle(m_left, m_top, getWidth(), getHeight());
    }

private:
    //coordinates
    T m_left;
    T m_top;
    T m_right;
    T m_bottom;

    friend class Transform;
};


/**
    Creates a rectangle.
    @param left left coordinate.
    @param top top coordinate
    @param right right coordinate.
    @param bottom bottom coordinate.
    @return a rectangle with the given coordinates.
 */
template <class T> Rect<T> makeRect(T left, T top, T right, T bottom) {
    return Rect<T>(left, top, right, bottom);
}


/**
    Creates a rectangle from point and size.
    @param pt top-left coordinate.
    @param sz size.
    @return a rectangle with the given top-left coordinate and size.
 */
template <class T> Rect<T> makeRect(const Point<T> &pt, const Size<T> &sz) {
    return Rect<T>(pt, sz);
}


} //namespace alx


/**
    Output a rectangle.
 */
template <class Char, class CharTraits, class T> std::basic_ostream<Char, CharTraits> &operator << (std::basic_ostream<Char, CharTraits> &stream, const alx::Rect<T> &rct) {
    std::cout << "[x=" << rct.getLeft() << " y=" << rct.getTop() << " w=" << rct.getWidth() << " h=" << rct.getHeight() << "]";
    return stream;
}


#endif //ALX_RECT_HPP
