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

private:
    int m_x;
    int m_y;
};


} //namespace alx


#endif //ALX_POINT_HPP