#ifndef ALX_SIZE_HPP
#define ALX_SIZE_HPP


namespace alx {


//TODO


template <class T> class Size {
public:
    Size(int width = 0, int height = 0) : m_width(width), m_height(height) {
    }

    int getWidth() const {
        return m_width;
    }

    int getHeight() const {
        return m_height;
    }

private:
    int m_width;
    int m_height;
};


} //namespace alx


#endif //ALX_SIZE_HPP