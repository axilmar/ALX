#ifndef ALX_TIMEOUT_HPP
#define ALX_TIMEOUT_HPP


#include <allegro5/allegro.h>
#include "alx/Value.hpp"


namespace alx {


/**
    Value-based wrapper aroundaAn ALLEGRO_TIMEOUT.
 */
class Timeout : public Value<ALLEGRO_TIMEOUT> {
public:
    /**
        The default constructor.
     */
    Timeout() {
    }

    /**
        constructor from timeout.
        @param timeout timeout.
     */
    Timeout(const ALLEGRO_TIMEOUT &timeout) : Value(timeout) {
    }

    /**
        constructor.
        @param seconds seconds.
     */
    Timeout(double seconds) {
        al_init_timeout(&get(), seconds);
    }
};


} //namespace alx


#endif //ALX_TIMEOUT_HPP
