#ifndef ALX_POINT_HPP
#define ALX_POINT_HPP


namespace alx {


/**
    A Point class.
    @param T type of coordinate.
 */
template <class T> class Point {
public:
    /**
        the default constructor.
        @param x default x value.
        @param y default y value.
     */
    Point(T x = 0, T y = 0) : m_x(x), m_y(y) {
    }

    /**
        Returns the x coordinate.
     */
    T getX() const {
        return m_x;
    }

    /**
        Returns the y coordinate.
     */
    T getY() const {
        return m_y;
    }

    /**
        Sets the x coordinate.
        @param x x value.
     */
    void setX(T x) {
        m_x = x;
    }

    /**
        Sets the y coordinate.
        @param y y value.
     */
    void setY(T y) {
        m_y = y;
    }

    /**
        Sets the x and y coordinates.
        @param x x value.
        @param y y value.
     */
    void set(T x, T y) {
        setX(x);
        setY(y);
    }

    /**
        Adds a point to this.
        @param pt point to add to this.
        @return reference to this.
     */
    Point<T> &operator += (const Point<T> &pt) {
        set(m_x + pt.m_x, m_y + pt.m_y);
        return *this;
    }

    /**
        Adds two points.
        @param a 1st point.
        @param b 2nd point.
        @return a point which contains the sum of both points.
     */
    friend Point<T> operator + (const Point<T> &a, const Point<T> &b) {
        return Point<T>(a.m_x + b.m_x, a.m_y + b.m_y);
    }

    /**
        Subtracts a point from this.
        @param pt point to subtract from this.
        @return reference to this.
     */
    Point<T> &operator -= (const Point<T> &pt) {
        set(m_x - pt.m_x, m_y - pt.m_y);
        return *this;
    }

    /**
        Subtracts two points.
        @param a 1st point.
        @param b 2nd point.
        @return a point which contains the difference of both points.
     */
    friend Point<T> operator - (const Point<T> &a, const Point<T> &b) {
        return Point<T>(a.m_x - b.m_x, a.m_y - b.m_y);
    }

    /**
        Multiplies a point to this.
        @param pt point to multiply to this.
        @return reference to this.
     */
    Point<T> &operator *= (const Point<T> &pt) {
        set(m_x * pt.m_x, m_y * pt.m_y);
        return *this;
    }

    /**
        Multiplies two points.
        @param a 1st point.
        @param b 2nd point.
        @return a point which contains the product of both points.
     */
    friend Point<T> operator * (const Point<T> &a, const Point<T> &b) {
        return Point<T>(a.m_x * b.m_x, a.m_y * b.m_y);
    }

    /**
        Divides this by a point.
        @param pt point to divide this by.
        @return reference to this.
     */
    Point<T> &operator /= (const Point<T> &pt) {
        set(m_x / pt.m_x, m_y / pt.m_y);
        return /this;
    }

    /**
        Divides two points.
        @param a 1st point.
        @param b 2nd point.
        @return a point which contains the quotient of both points.
     */
    friend Point<T> operator / (const Point<T> &a, const Point<T> &b) {
        return Point<T>(a.m_x / b.m_x, a.m_y / b.m_y);
    }

    /**
        Divides this by a point and sets the modulo.
        @param pt point to divide this by.
        @return reference to this.
     */
    Point<T> &operator %= (const Point<T> &pt) {
        set(m_x % pt.m_x, m_y % pt.m_y);
        return %this;
    }

    /**
        Divides two points and returns the modulo.
        @param a 1st point.
        @param b 2nd point.
        @return a point which contains the modulo of the division of both points.
     */
    friend Point<T> operator % (const Point<T> &a, const Point<T> &b) {
        return Point<T>(a.m_x % b.m_x, a.m_y % b.m_y);
    }

    /**
        Adds a value to both coordinates.
        @param val value to add.
        @return reference to this.
     */
    Point<T> &operator += (T val) {
        set(m_x + val, m_y + val);
        return *this;
    }

    /**
        Adds a value to a point and creates a new point.
        @param val value to add.
        @return a new point.
     */
    Point<T> operator + (T val) const {
        return Point<T>(m_x + val, m_y + val);
    }

    /**
        Subtracts a value from both coordinates.
        @param val value to subtract.
        @return reference to this.
     */
    Point<T> &operator -= (T val) {
        set(m_x - val, m_y - val);
        return *this;
    }

    /**
        Subtracts a value from a point and creates a new point.
        @param val value to subtract.
        @return a new point.
     */
    Point<T> operator - (T val) const {
        return Point<T>(m_x - val, m_y - val);
    }

    /**
        Multiplies a value to both coordinates.
        @param val value to multiply this with.
        @return reference to this.
     */
    Point<T> &operator *= (T val) {
        set(m_x * val, m_y * val);
        return *this;
    }

    /**
        Multiplies a value to a point and creates a new point.
        @param val value to multiply this with.
        @return a new point.
     */
    Point<T> operator * (T val) const {
        return Point<T>(m_x * val, m_y * val);
    }

    /**
        Divides both coordinates by a value.
        @param val value to divide this with.
        @return reference to this.
     */
    Point<T> &operator /= (T val) {
        set(m_x / val, m_y / val);
        return *this;
    }

    /**
        Divides a point by a value and creates a new point.
        @param val value to divide this with.
        @return a new point.
     */
    Point<T> operator / (T val) const {
        return Point<T>(m_x / val, m_y / val);
    }

    /**
        Sets both coordinates to the modulo of the division.
        @param val value to divide this with.
        @return reference to this.
     */
    Point<T> &operator %= (T val) {
        set(m_x % val, m_y % val);
        return *this;
    }

    /**
        Divides a point by a value and creates a new point with the modulo.
        @param val value to divide this with.
        @return a new point.
     */
    Point<T> operator % (T val) const {
        return Point<T>(m_x % val, m_y % val);
    }

private:
    //coordinates
    T m_x;
    T m_y;

    friend class Transform;
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