#ifndef ALX_SIZE_HPP
#define ALX_SIZE_HPP


#include "Vector2.hpp"


namespace alx {


/**
    A size object.
    @param T type of member.
 */
template <class T> class Size : public Vector2<T> {
public:
    /**
        The default constructor.
        @param width the default width.
        @param height the default height.
     */
    Size(T width = 0, T height = 0) : Vector2<T>(width, height) {
    }

    /**
        Returns the width.
        @return the width.
     */
    T getWidth() const {
        return Vector2<T>::getX();
    }

    /**
        Returns the height.
        @return the height.
     */
    T getHeight() const {
        return Vector2<T>::getY();
    }

    /**
        Returns width * height.
        @return width * height.
     */
    T getArea() const {
        return Vector2<T>::getProduct();
    }

    /**
        Less-than test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator < (const Size<T> &pt) const {
        return getArea() < pt.getArea();
    }

    /**
        Less-than-or-equal test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator <= (const Size<T> &pt) const {
        return getArea() <= pt.getArea();
    }

    /**
        Greater-than test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator > (const Size<T> &pt) const {
        return getArea() > pt.getArea();
    }

    /**
        Greater-than-or-equal test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator >= (const Size<T> &pt) const {
        return getArea() >= pt.getArea();
    }

    /**
        Sets the width.
        @param w new width.
     */
    void setWidth(T w) {
        setX(w);
    }

    /**
        Sets the height.
        @param h new height.
     */
    void setHeight(T h) {
        setY(h);
    }

    /**
        Sets both the width and height.
        @param w new width.
        @param h new height.
     */
    void set(T w, T h) {
        setWidth(w);
        setHeight(h);
    }

};


/**
    Creates a size.
    @param w width.
    @param h height.
    @return a size with the given values.
 */
template <class T> Size<T> makeSize(T w, T h) {
    return Size<T>(w, h);
}


} //namespace alx


#endif //ALX_SIZE_HPP
