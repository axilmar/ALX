#ifndef ALX_VECTOR2_HPP
#define ALX_VECTOR2_HPP


#include "Vector2Base.hpp"


namespace alx {


/**
    A 2d vector class.
    @param T type of coordinate.
 */
template <class T> class Vector2 : public Vector2Base<Vector2<T>, T> {
public:
    using Vector2Base<Vector2<T>, T>::Vector2Base<Vector2<T>, T>;
};


/**
    Creates a vector.
    @param x x coordinate.
    @param y y coordinate.
    @return a vector with the given coordinates.
 */
template <class T> Vector2<T> makeVector2(T x, T y) {
    return Vector2<T>(x, y);
}


} //namespace alx


#endif //ALX_VECTOR2_HPP
