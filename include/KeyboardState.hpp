#ifndef ALX_KEYBOARDSTATE_HPP
#define ALX_KEYBOARDSTATE_HPP


#include <allegro5/allegro.h>
#include "Value.hpp"


namespace alx {


/**
    an ALLEGRO_KEYBOARD_STATE.
 */
class KeyboardState : public Value<ALLEGRO_KEYBOARD_STATE> {
public:
    /**
        The default constructor.
     */
    KeyboardState() {
    }

    /**
        constructor from state.
        @param state state.
     */
    KeyboardState(const ALLEGRO_KEYBOARD_STATE &state) : Value(state) {
    }

    /**
        Retrieves the keyboard state.
     */
    void retrieve() {
        al_get_keyboard_state(&get());
    }

    /**
        Checks if a key was down in this state.
        @param keycode key code.
        @return true if the key was down.
     */
    bool isKeyDown(int keycode) const {
        return al_key_down(&get(), keycode);
    }
};


} //namespace alx


#endif //ALX_KEYBOARDSTATE_HPP
