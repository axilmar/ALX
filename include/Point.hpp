#ifndef ALX_POINT_HPP
#define ALX_POINT_HPP


#include "Vector2.hpp"


namespace alx {


/**
    A Point class.
    @param T type of coordinate.
 */
template <class T> class Point : public Vector2<T> {
public:
    /**
        the default constructor.
        @param x default x value.
        @param y default y value.
     */
    Point(T x = 0, T y = 0) : Vector2(x, y) {
    }
};


/**
    Creates a point.
    @param x x coordinate.
    @param y y coordinate.
    @return a point with the given coordinates.
 */
template <class T> Point<T> makePoint(T x, T y) {
    return Point<T>(x, y);
}


} //namespace alx


#endif //ALX_POINT_HPP