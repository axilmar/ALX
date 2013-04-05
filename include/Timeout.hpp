#ifndef ALX_TIMEOUT_HPP
#define ALX_TIMEOUT_HPP


#include <allegro5/allegro.h>


namespace alx {


/**
    An ALLEGRO_TIMEOUT value.
 */
class Timeout : private ALLEGRO_TIMEOUT {
public:
    /**
        constructor.
        @param seconds seconds.
     */
    Timeout(double seconds) {
        al_init_timeout(this, seconds);
    }

private:
    friend class Condition;
};


} //namespace alx


#endif //ALX_TIMEOUT_HPP
