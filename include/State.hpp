#ifndef ALX_STATE_HPP
#define ALX_STATE_HPP


#include <allegro5/allegro.h>
#include "Value.hpp"


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_STATE.
 */
class State : public Value<ALLEGRO_STATE> {
public:
    /**
        Restores the state.
     */
    void restore() const {
        al_restore_state(&get());
    }

    /**
        Retrieves the state.
     */
    void retrieve(int flags) {
        al_store_state(&get(), flags);
    }
};


} //namespace alx


#endif //ALX_STATE_HPP
