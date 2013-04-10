#ifndef ALX_POINT_HPP
#define ALX_POINT_HPP


namespace alx {


//TODO


template <class T> class Point {
public:
    Point(int x = 0, int y = 0) : m_x(x), m_y(y) {
    }

    int getX() const {
        return m_x;
    }

    int getY() const {
        return m_y;
    }

    void set(T x, T y) {
        m_x = x;
        m_y = y;
    }

private:
    T m_x;
    T m_y;

    friend class Transform;
};


template <class T> Point<T> makePoint(T x, T y) {
    return Point<T>(x, y);
}


} //namespace alx


#endif //ALX_POINT_HPP