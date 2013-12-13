#ifndef ALX_STATE_HPP
#define ALX_STATE_HPP


#include <allegro5/allegro.h>
#include "alx/Value.hpp"


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_STATE.
 */
class State : public Value<ALLEGRO_STATE> {
public:
    /**
        The default constructor.
     */
    State() {
    }

    /**
        constructor from state.
        @param state state.
     */
    State(const ALLEGRO_STATE &state) : Value(state) {
    }

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
