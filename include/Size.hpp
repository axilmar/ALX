#ifndef ALX_SIZE_HPP
#define ALX_SIZE_HPP


namespace alx {


/**
    A size object.
    @param T type of member.
 */
template <class T> class Size {
public:
    /**
        The default constructor.
        @param width the default width.
        @param height the default height.
     */
    Size(T width = 0, T height = 0) : m_width(width), m_height(height) {
    }

    /**
        Returns the width.
        @return the width.
     */
    T getWidth() const {
        return m_width;
    }

    /**
        Returns the height.
        @return the height.
     */
    T getHeight() const {
        return m_height;
    }

    /**
        Returns width * height.
        @return width * height.
     */
    T getAreaLength() const {
        return m_width * m_height;
    }

    /**
        Equality test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator == (const Size<T> &pt) const {
        return m_width == pt.m_width && m_height == pt.m_height;
    }

    /**
        Difference test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator != (const Size<T> &pt) const {
        return !operator == (pt);
    }

    /**
        Less-than test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator < (const Size<T> &pt) const {
        return getAreaLength() < pt.getAreaLength();
    }

    /**
        Less-than-or-equal test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator <= (const Size<T> &pt) const {
        return getAreaLength() <= pt.getAreaLength();
    }

    /**
        Greater-than test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator > (const Size<T> &pt) const {
        return getAreaLength() > pt.getAreaLength();
    }

    /**
        Greater-than-or-equal test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator >= (const Size<T> &pt) const {
        return getAreaLength() >= pt.getAreaLength();
    }

    /**
        Sets the width.
        @param w new width.
     */
    void setWidth(T w) {
        m_width = w;
    }

    /**
        Sets the height.
        @param h new height.
     */
    void setHeight(T h) {
        m_height = h;
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

    /**
        Adds a size to this.
        @param sz size to add to this.
        @return reference to this.
     */
    Size<T> &operator += (const Size<T> &sz) {
        set(m_width + sz.m_width, m_height + sz.m_height);
        return *this;
    }

    /**
        Adds two sizes.
        @param a 1st size.
        @param b 2nd size.
        @return a size which contains the sum of both sizes.
     */
    friend Size<T> operator + (const Size<T> &a, const Size<T> &b) {
        return Size<T>(a.m_width + b.m_width, a.m_height + b.m_height);
    }

    /**
        Subtracts a size from this.
        @param sz size to subtract from this.
        @return reference to this.
     */
    Size<T> &operator -= (const Size<T> &sz) {
        set(m_width - sz.m_width, m_height - sz.m_height);
        return *this;
    }

    /**
        Subtracts two sizes.
        @param a 1st size.
        @param b 2nd size.
        @return a size which contains the difference of both sizes.
     */
    friend Size<T> operator - (const Size<T> &a, const Size<T> &b) {
        return Size<T>(a.m_width - b.m_width, a.m_height - b.m_height);
    }

    /**
        Multiplies a size to this.
        @param sz size to multiply to this.
        @return reference to this.
     */
    Size<T> &operator *= (const Size<T> &sz) {
        set(m_width * sz.m_width, m_height * sz.m_height);
        return *this;
    }

    /**
        Multiplies two sizes.
        @param a 1st size.
        @param b 2nd size.
        @return a size which contains the product of both sizes.
     */
    friend Size<T> operator * (const Size<T> &a, const Size<T> &b) {
        return Size<T>(a.m_width * b.m_width, a.m_height * b.m_height);
    }

    /**
        Divides this by a size.
        @param sz size to divide this by.
        @return reference to this.
     */
    Size<T> &operator /= (const Size<T> &sz) {
        set(m_width / sz.m_width, m_height / sz.m_height);
        return /this;
    }

    /**
        Divides two sizes.
        @param a 1st size.
        @param b 2nd size.
        @return a size which contains the quotient of both sizes.
     */
    friend Size<T> operator / (const Size<T> &a, const Size<T> &b) {
        return Size<T>(a.m_width / b.m_width, a.m_height / b.m_height);
    }

    /**
        Divides this by a size and sets the modulo.
        @param sz size to divide this by.
        @return reference to this.
     */
    Size<T> &operator %= (const Size<T> &sz) {
        set(m_width % sz.m_width, m_height % sz.m_height);
        return %this;
    }

    /**
        Divides two sizes and returns the modulo.
        @param a 1st size.
        @param b 2nd size.
        @return a size which contains the modulo of the division of both sizes.
     */
    friend Size<T> operator % (const Size<T> &a, const Size<T> &b) {
        return Size<T>(a.m_width % b.m_width, a.m_height % b.m_height);
    }

    /**
        Adds a value to both coordinates.
        @param val value to add.
        @return reference to this.
     */
    Size<T> &operator += (T val) {
        set(m_width + val, m_height + val);
        return *this;
    }

    /**
        Adds a value to a size and creates a new size.
        @param val value to add.
        @return a new size.
     */
    Size<T> operator + (T val) const {
        return Size<T>(m_width + val, m_height + val);
    }

    /**
        Subtracts a value from both coordinates.
        @param val value to subtract.
        @return reference to this.
     */
    Size<T> &operator -= (T val) {
        set(m_width - val, m_height - val);
        return *this;
    }

    /**
        Subtracts a value from a size and creates a new size.
        @param val value to subtract.
        @return a new size.
     */
    Size<T> operator - (T val) const {
        return Size<T>(m_width - val, m_height - val);
    }

    /**
        Multiplies a value to both coordinates.
        @param val value to multiply this with.
        @return reference to this.
     */
    Size<T> &operator *= (T val) {
        set(m_width * val, m_height * val);
        return *this;
    }

    /**
        Multiplies a value to a size and creates a new size.
        @param val value to multiply this with.
        @return a new size.
     */
    Size<T> operator * (T val) const {
        return Size<T>(m_width * val, m_height * val);
    }

    /**
        Divides both coordinates by a value.
        @param val value to divide this with.
        @return reference to this.
     */
    Size<T> &operator /= (T val) {
        set(m_width / val, m_height / val);
        return *this;
    }

    /**
        Divides a size by a value and creates a new size.
        @param val value to divide this with.
        @return a new size.
     */
    Size<T> operator / (T val) const {
        return Size<T>(m_width / val, m_height / val);
    }

    /**
        Sets both coordinates to the modulo of the division.
        @param val value to divide this with.
        @return reference to this.
     */
    Size<T> &operator %= (T val) {
        set(m_width % val, m_height % val);
        return *this;
    }

    /**
        Divides a size by a value and creates a new size with the modulo.
        @param val value to divide this with.
        @return a new size.
     */
    Size<T> operator % (T val) const {
        return Size<T>(m_width % val, m_height % val);
    }

private:
    //members
    T m_width;
    T m_height;
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
