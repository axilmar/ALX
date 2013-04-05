#ifndef ALX_JOYSTICKSTATE_HPP
#define ALX_JOYSTICKSTATE_HPP


#include "Joystick.hpp"


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_JOYSTICK_STATE.
 */
class JoystickState {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    JoystickState(ALLEGRO_JOYSTICK_STATE *object, bool managed = true) : m_object(object, managed ? _deleteState : [](ALLEGRO_JOYSTICK_STATE *){}) {
    }

    /**
        Creates a joystick state.
     */
    JoystickState() : m_object(new ALLEGRO_JOYSTICK_STATE) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Reads the given joystick's state.
        @param stick joystick.
     */
    void readState(const Joystick &stick) {
        al_get_joystick_state(stick.m_object.get(), m_object.get());    
    }

    /**
        Returns the status of a button.
        @param button button index.
        @return button index or -1 if the index is invalid.
     */
    int getButton(int button) const {
        return button >= 0 && button < _AL_MAX_JOYSTICK_BUTTONS ? m_object->button[button] : -1;
    }

    /**
        Returns the axis value for the given stick.
        @param stick stick index.
        @param axis axis index.
        @return axis value or FLT_MAX if the stick index is invalid.
     */
    float getAxis(int stick, int axis) const {
        return stick >= 0 && stick < _AL_MAX_JOYSTICK_STICKS && axis >= 0 && axis < _AL_MAX_JOYSTICK_AXES ? m_object->stick[stick].axis[axis] : FLT_MAX;
    }

private:
    //allegro object
    std::shared_ptr<ALLEGRO_JOYSTICK_STATE> m_object;

    //state deleter
    static void _deleteState(ALLEGRO_JOYSTICK_STATE *state) {
        delete state;
    }
};


} //namespace alx


#endif //ALX_JOYSTICKSTATE_HPP
