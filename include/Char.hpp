#ifndef ALX_CHAR_HPP
#define ALX_CHAR_HPP


#include "Value.hpp"


namespace alx {


/**
    Provides a strongly-typed character implementation.
 */
class Char : public Value<int> {
public:
    /**
        Constructor.
        @param v value.
     */
    Char(int v = 0) : Value(v) {
    }
};


} //namespace alx


#endif //ALX_CHAR_HPP
