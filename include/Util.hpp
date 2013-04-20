#ifndef ALX_UTIL_HPP
#define ALX_UTIL_HPP


#include <algorithm>
#include <allegro5/allegro.h>


namespace alx {


/**
    Class with utility functions.
 */
class Util {
public:
    /**
        Checks if this program runs in little or big endian mode.
     */
    static bool isLittleEndian() {
        static const union {uint16_t x; uint8_t b;} x = {1};
        return x.b;
    }

    /**
        Swaps endianess of the given value.
        @param v value to swap endianess for.
        @return the converted value.
     */
    template <class T> static T swapEndianess(T v) {
        union {
            T v;
            uint8_t b[sizeof(T)];
        } r = {v};
        for(int i = 0; i < sizeof(T)/2; ++i) {
            std::swap(r.b[i], r.b[sizeof(T) - 1 - i]);
        }
        return r.v;
    }

    /**
        Converts the endianess of the given variable from little to native, if needed.
        @param v input value.
        @return converted value.
     */
    template <class T> static T littleToNativeEndian(T v) {
        return isLittleEndian() ? v : swapEndianess(v);
    }

    /**
        Converts the endianess of the given variable from big to native, if needed.
        @param v input value.
        @return converted value.
     */
    template <class T> static T bigToNativeEndian(T v) {
        return !isLittleEndian() ? v : swapEndianess(v);
    }

    /**
        Converts the endianess of the given variable from native to little, if needed.
        @param v input value.
        @return converted value.
     */
    template <class  T> static T nativeToLittleEndian(T v) {
        return isLittleEndian() ? v : swapEndianess(v);
    }

    /**
        Converts the endianess of the given variable from native to big, if needed.
        @param v input value.
        @return converted value.
     */
    template <class  T> static T nativeToBigEndian(T v) {
        return !isLittleEndian() ? v : swapEndianess(v);
    }
};


} //namespace alx


#endif //ALX_UTIL_HPP

