#ifndef ALX_FIXED_HPP
#define ALX_FIXED_HPP


#include <allegro5/allegro.h>


namespace alx {


/**
    A fixed number.
 */
class Fixed {
public:
    /**
        The default constructor.
        @param v value.
     */
    Fixed(int v = 0) : m_value(al_itofix(v)) {
    }

    /**
        constructor from double.
        @param v value.
     */
    Fixed(double v) : m_value(al_ftofix(v)) {
    }

    /**
        conversion to integer.
        @return integer.
     */
    operator int () const {
        return al_fixtoi(m_value);
    }

    /**
        conversion to double.
        @return double.
     */
    operator double () const {
        return al_fixtof(m_value);
    }

    /**
        Returns the integer which is less than the value of this.
        @return the integer which is less than the value of this.
     */
    int floor() const {
        return al_fixfloor(m_value);
    }

    /**
        Returns the integer which is greater than the value of this.
        @return the integer which is greater than the value of this.
     */
    int ceil() const {
        return al_fixceil(m_value);
    }

    /**
        Equality test with fixed value.
        @param v value.
        @return true if the test succeeds.
     */
    bool operator == (Fixed v) {
        return m_value == v.m_value;
    }

    /**
        Difference test with fixed value.
        @param v value.
        @return true if the test succeeds.
     */
    bool operator != (Fixed v) {
        return m_value != v.m_value;
    }

    /**
        Less than test with fixed value.
        @param v value.
        @return true if the test succeeds.
     */
    bool operator < (Fixed v) {
        return m_value < v.m_value;
    }

    /**
        Less than or equal test with fixed value.
        @param v value.
        @return true if the test succeeds.
     */
    bool operator <= (Fixed v) {
        return m_value <= v.m_value;
    }

    /**
        Greater than test with fixed value.
        @param v value.
        @return true if the test succeeds.
     */
    bool operator > (Fixed v) {
        return m_value > v.m_value;
    }

    /**
        Greater than or equal test with fixed value.
        @param v value.
        @return true if the test succeeds.
     */
    bool operator >= (Fixed v) {
        return m_value >= v.m_value;
    }

    /**
        Sets the value from integer.
        @param v value.
        @return reference to this.
     */
    Fixed &operator = (int v) {
        m_value = al_itofix(v);
        return *this;
    }

    /**
        Sets the value from double.
        @param v value.
        @return reference to this.
     */
    Fixed &operator = (double v) {
        m_value = al_itofix(v);
        return *this;
    }

    /**
        Adds two fixed numbers.
        @param a 1st value.
        @param b 2nd value.
        @return result of operation.
     */
    friend Fixed operator + (Fixed a, Fixed b) {
        return make(al_fixadd(a.m_value, b.m_value));
    }

    /**
        Adds a fixed number to this.
        @param v value.
        @return result of operation.
     */
    Fixed &operator += (Fixed v) {
        m_value = al_fixadd(m_value, v.m_value);
        return *this;
    }

    /**
        Subtracts two fixed numbers.
        @param a 1st value.
        @param b 2nd value.
        @return result of operation.
     */
    friend Fixed operator - (Fixed a, Fixed b) {
        return make(al_fixsub(a.m_value, b.m_value));
    }

    /**
        Subtracts a fixed number to this.
        @param v value.
        @return result of operation.
     */
    Fixed &operator -= (Fixed v) {
        m_value = al_fixsub(m_value, v.m_value);
        return *this;
    }

    /**
        Multiplies two fixed numbers.
        @param a 1st value.
        @param b 2nd value.
        @return result of operation.
     */
    friend Fixed operator * (Fixed a, Fixed b) {
        return make(al_fixmul(a.m_value, b.m_value));
    }

    /**
        Multiplies a fixed number to this.
        @param v value.
        @return result of operation.
     */
    Fixed &operator *= (Fixed v) {
        m_value = al_fixmul(m_value, v.m_value);
        return *this;
    }

    /**
        Divides two fixed numbers.
        @param a 1st value.
        @param b 2nd value.
        @return result of operation.
     */
    friend Fixed operator / (Fixed a, Fixed b) {
        return make(al_fixdiv(a.m_value, b.m_value));
    }

    /**
        Divides this by a fixed number.
        @param v value.
        @return result of operation.
     */
    Fixed &operator /= (Fixed v) {
        m_value = al_fixdiv(m_value, v.m_value);
        return *this;
    }

    /**
        Modulo of two fixed numbers.
        @param a 1st value.
        @param b 2nd value.
        @return result of operation.
     */
    friend Fixed operator % (Fixed a, Fixed b) {
        return fmod(al_fixtof(a.m_value), al_fixtof(b.m_value));
    }

    /**
        Modulo of this by a fixed number.
        @param v value.
        @return result of operation.
     */
    Fixed &operator %= (Fixed v) {
        m_value = al_ftofix(fmod(al_fixtof(m_value), al_fixtof(v.m_value)));
        return *this;
    }

    /**
        Left shift.
        @param a 1st value.
        @param b 2nd value.
        @return result of operation.
     */
    friend Fixed operator << (Fixed a, int b) {
        return make(a.m_value << b);
    }

    /**
        Left shift assignment.
        @param v value.
        @return result of operation.
     */
    Fixed &operator <<= (int v) {
        m_value <<= v;
        return *this;
    }

    /**
        Right shift.
        @param a 1st value.
        @param b 2nd value.
        @return result of operation.
     */
    friend Fixed operator >> (Fixed a, int b) {
        return make(a.m_value >> b);
    }

    /**
        Right shift assignment.
        @param v value.
        @return result of operation.
     */
    Fixed &operator >>= (int v) {
        m_value >>= v;
        return *this;
    }

private:
    //value
    al_fixed m_value;

    //internal constructor used to avoiding erroneous type conversions
    Fixed(al_fixed v, bool d) : m_value(v) {
    }

    //make fixed
    static Fixed make(al_fixed v) {
        return Fixed(v, true);
    }
};


} //namespace alx


#endif //ALX_FIXED_HPP
