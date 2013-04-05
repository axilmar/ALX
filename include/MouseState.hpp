#ifndef ALX_MOUSESTATE_HPP
#define ALX_MOUSESTATE_HPP


#include <allegro5/allegro.h>
#include "Value.hpp"


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_MOUSE_STATE.
 */
class MouseState : public Value<ALLEGRO_MOUSE_STATE> {
public:
    /**
        Retrieves the mouse state.
     */
    void retrieve() {
        al_get_mouse_state(&get());
    }

    /**
        Returns the given axis' value.
        @param axis asix index.
        @return the given axis' value.
     */
    int getAxis(int axis) const {
        return al_get_mouse_state_axis(&get(), axis);
    }

    /**
        Checks if a button was down in this state.
        @param button button index; 1 for first button.
        @return true if the key was down.
     */
    bool isButtonDown(int button) const {
        return al_mouse_button_down(&get(), button);
    }
};


} //namespace alx


#endif //ALX_MOUSESTATE_HPP
