#ifndef ALX_JOYSTICKSTATE_HPP
#define ALX_JOYSTICKSTATE_HPP


#include "Joystick.hpp"
#include "Value.hpp"


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_JOYSTICK_STATE.
 */
class JoystickState : public Value<ALLEGRO_JOYSTICK_STATE> {
public:
    /**
        Reads the given joystick's state.
        @param stick joystick.
     */
    void retrieve(const Joystick &stick) {
        al_get_joystick_state(stick.get(), &get());    
    }

    /**
        Returns the status of a button.
        @param button button index.
        @return button index or -1 if the index is invalid.
     */
    int getButton(int button) const {
        return button >= 0 && button < _AL_MAX_JOYSTICK_BUTTONS ? get().button[button] : -1;
    }

    /**
        Returns the axis value for the given stick.
        @param stick stick index.
        @param axis axis index.
        @return axis value or FLT_MAX if the stick index is invalid.
     */
    float getAxis(int stick, int axis) const {
        return stick >= 0 && stick < _AL_MAX_JOYSTICK_STICKS && axis >= 0 && axis < _AL_MAX_JOYSTICK_AXES ? get().stick[stick].axis[axis] : FLT_MAX;
    }

private:
    //state deleter
    static void _deleteState(ALLEGRO_JOYSTICK_STATE *state) {
        delete state;
    }
};


} //namespace alx


#endif //ALX_JOYSTICKSTATE_HPP
