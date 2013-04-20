#ifndef ALX_VECTOR2_HPP
#define ALX_VECTOR2_HPP


namespace alx {


/**
    A 2d vector class.
    @param T type of coordinate.
 */
template <class T> class Vector2 {
public:
    /**
        the default constructor.
        @param x default x value.
        @param y default y value.
     */
    Vector2(T x = 0, T y = 0) : m_x(x), m_y(y) {
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
        Equality test.
        @param pt the other vector to compare this to.
        @return true if the test is successful.
     */
    bool operator == (const Vector2<T> &pt) const {
        return m_x == pt.m_x && m_y == pt.m_y;
    }

    /**
        Difference test.
        @param pt the other vector to compare this to.
        @return true if the test is successful.
     */
    bool operator != (const Vector2<T> &pt) const {
        return !operator == (pt);
    }

    /**
        Less-than test.
        @param pt the other vector to compare this to.
        @return true if the test is successful.
     */
    bool operator < (const Vector2<T> &pt) const {
        return m_y < pt.m_y || (m_y == pt.m_y && m_x < pt.m_x);
    }

    /**
        Less-than-or-equal test.
        @param pt the other vector to compare this to.
        @return true if the test is successful.
     */
    bool operator <= (const Vector2<T> &pt) const {
        return m_y < pt.m_y || (m_y == pt.m_y && m_x <= pt.m_x);
    }

    /**
        Greater-than test.
        @param pt the other vector to compare this to.
        @return true if the test is successful.
     */
    bool operator > (const Vector2<T> &pt) const {
        return m_y > pt.m_y || (m_y == pt.m_y && m_x > pt.m_x);
    }

    /**
        Greater-than-or-equal test.
        @param pt the other vector to compare this to.
        @return true if the test is successful.
     */
    bool operator >= (const Vector2<T> &pt) const {
        return m_y > pt.m_y || (m_y == pt.m_y && m_x >= pt.m_x);
    }

    /**
        Returns x * y.
        @return x * y.
     */
    T getProduct() const {
        return m_x * m_y;
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
        Adds a vector to this.
        @param pt vector to add to this.
        @return reference to this.
     */
    Vector2<T> &operator += (const Vector2<T> &pt) {
        set(m_x + pt.m_x, m_y + pt.m_y);
        return *this;
    }

    /**
        Adds two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the sum of both points.
     */
    friend Vector2<T> operator + (const Vector2<T> &a, const Vector2<T> &b) {
        return Vector2<T>(a.m_x + b.m_x, a.m_y + b.m_y);
    }

    /**
        Subtracts a vector from this.
        @param pt vector to subtract from this.
        @return reference to this.
     */
    Vector2<T> &operator -= (const Vector2<T> &pt) {
        set(m_x - pt.m_x, m_y - pt.m_y);
        return *this;
    }

    /**
        Subtracts two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the difference of both points.
     */
    friend Vector2<T> operator - (const Vector2<T> &a, const Vector2<T> &b) {
        return Vector2<T>(a.m_x - b.m_x, a.m_y - b.m_y);
    }

    /**
        Multiplies a vector to this.
        @param pt vector to multiply to this.
        @return reference to this.
     */
    Vector2<T> &operator *= (const Vector2<T> &pt) {
        set(m_x * pt.m_x, m_y * pt.m_y);
        return *this;
    }

    /**
        Multiplies two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the product of both points.
     */
    friend Vector2<T> operator * (const Vector2<T> &a, const Vector2<T> &b) {
        return Vector2<T>(a.m_x * b.m_x, a.m_y * b.m_y);
    }

    /**
        Divides this by a vector.
        @param pt vector to divide this by.
        @return reference to this.
     */
    Vector2<T> &operator /= (const Vector2<T> &pt) {
        set(m_x / pt.m_x, m_y / pt.m_y);
        return *this;
    }

    /**
        Divides two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the quotient of both points.
     */
    friend Vector2<T> operator / (const Vector2<T> &a, const Vector2<T> &b) {
        return Vector2<T>(a.m_x / b.m_x, a.m_y / b.m_y);
    }

    /**
        Divides this by a vector and sets the modulo.
        @param pt vector to divide this by.
        @return reference to this.
     */
    Vector2<T> &operator %= (const Vector2<T> &pt) {
        set(m_x % pt.m_x, m_y % pt.m_y);
        return *this;
    }

    /**
        Divides two points and returns the modulo.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the modulo of the division of both points.
     */
    friend Vector2<T> operator % (const Vector2<T> &a, const Vector2<T> &b) {
        return Vector2<T>(a.m_x % b.m_x, a.m_y % b.m_y);
    }

    /**
        Adds a value to both coordinates.
        @param val value to add.
        @return reference to this.
     */
    Vector2<T> &operator += (T val) {
        set(m_x + val, m_y + val);
        return *this;
    }

    /**
        Adds a value to a vector and creates a new vector.
        @param val value to add.
        @return a new vector.
     */
    Vector2<T> operator + (T val) const {
        return Vector2<T>(m_x + val, m_y + val);
    }

    /**
        Subtracts a value from both coordinates.
        @param val value to subtract.
        @return reference to this.
     */
    Vector2<T> &operator -= (T val) {
        set(m_x - val, m_y - val);
        return *this;
    }

    /**
        Subtracts a value from a vector and creates a new vector.
        @param val value to subtract.
        @return a new vector.
     */
    Vector2<T> operator - (T val) const {
        return Vector2<T>(m_x - val, m_y - val);
    }

    /**
        Multiplies a value to both coordinates.
        @param val value to multiply this with.
        @return reference to this.
     */
    Vector2<T> &operator *= (T val) {
        set(m_x * val, m_y * val);
        return *this;
    }

    /**
        Multiplies a value to a vector and creates a new vector.
        @param val value to multiply this with.
        @return a new vector.
     */
    Vector2<T> operator * (T val) const {
        return Vector2<T>(m_x * val, m_y * val);
    }

    /**
        Divides both coordinates by a value.
        @param val value to divide this with.
        @return reference to this.
     */
    Vector2<T> &operator /= (T val) {
        set(m_x / val, m_y / val);
        return *this;
    }

    /**
        Divides a vector by a value and creates a new vector.
        @param val value to divide this with.
        @return a new vector.
     */
    Vector2<T> operator / (T val) const {
        return Vector2<T>(m_x / val, m_y / val);
    }

    /**
        Sets both coordinates to the modulo of the division.
        @param val value to divide this with.
        @return reference to this.
     */
    Vector2<T> &operator %= (T val) {
        set(m_x % val, m_y % val);
        return *this;
    }

    /**
        Divides a vector by a value and creates a new vector with the modulo.
        @param val value to divide this with.
        @return a new vector.
     */
    Vector2<T> operator % (T val) const {
        return Vector2<T>(m_x % val, m_y % val);
    }

private:
    //coordinates
    T m_x;
    T m_y;

    friend class Transform;
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
