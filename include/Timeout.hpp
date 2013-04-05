#ifndef ALX_TIMEOUT_HPP
#define ALX_TIMEOUT_HPP


#include <allegro5/allegro.h>


namespace alx {


/**
    An ALLEGRO_TIMEOUT.
 */
class Timeout {
public:
    /**
        constructor.
        @param seconds seconds.
     */
    Timeout(double seconds) {
        al_init_timeout(&m_object, seconds);
    }

private:
    ALLEGRO_TIMEOUT m_object;

    friend class Condition;
};


} //namespace alx


#endif //ALX_TIMEOUT_HPP
