#ifndef ALX_TIMEOUT_HPP
#define ALX_TIMEOUT_HPP


#include <allegro5/allegro.h>
#include "Value.hpp"


namespace alx {


/**
    Value-based wrapper aroundaAn ALLEGRO_TIMEOUT.
 */
class Timeout : public Value<ALLEGRO_TIMEOUT> {
public:
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
