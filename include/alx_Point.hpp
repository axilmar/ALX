#ifndef ALX_POINT_HPP
#define ALX_POINT_HPP


#include "alx_Vector2Base.hpp"


namespace alx {


/**
    A Point class.
    @param T type of coordinate.
 */
template <class T> class Point : public Vector2Base<Point<T>, T> {
public:
    /**
        constructor from x and y coordinates.
     */
    Point(T x = T(), T y = T()) : Vector2Base<Point<T>, T>(x, y) {
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
