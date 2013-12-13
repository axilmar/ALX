#ifndef ALX_VALUE_HPP
#define ALX_VALUE_HPP


namespace alx {


/**
    Base class for value-based wrapper classes.
 */
template <class T> class Value {
public:
    /**
        returns the value.
        @return the value.
     */
    operator const T &() const {
        return m_value;
    }

    /**
        returns the value.
        @return the value.
     */
    operator T &() {
        return m_value;
    }

    /**
        returns the value.
        @return the value.
     */
    const T &get() const {
        return m_value;
    }

    /**
        returns the value.
        @return the value.
     */
    T &get() {
        return m_value;
    }

protected:
    /**
        Default constructor.
     */
    Value() {
    }

    /**
        constructor from value.
     */
    Value(const T &value) : m_value(value) {
    }

private:
    //value
    T m_value;
};


} //namespace alx


#endif //ALX_VALUE_HPP
