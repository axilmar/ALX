#ifndef ALX_MOUSESTATE_HPP
#define ALX_MOUSESTATE_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_MOUSE_STATE.
 */
class MouseState {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    MouseState(ALLEGRO_MOUSE_STATE *object, bool managed = true) : m_object(object, managed ? [](ALLEGRO_MOUSE_STATE *state){ delete state; } : [](ALLEGRO_MOUSE_STATE *state){}) {
    }

    /**
        Creates a keyboard state.
     */
    MouseState() : m_object(new ALLEGRO_MOUSE_STATE) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Retrieves the mouse state.
     */
    void get() {
        al_get_mouse_state(m_object.get());
    }

    /**
        Returns the given axis' value.
        @param axis asix index.
        @return the given axis' value.
     */
    int getAxis(int axis) const {
        return al_get_mouse_state_axis(m_object.get(), axis);
    }

    /**
        Checks if a button was down in this state.
        @param button button index; 1 for first button.
        @return true if the key was down.
     */
    bool isButtonDown(int button) const {
        return al_mouse_button_down(m_object.get(), button);
    }

private:
    //allegro object
    std::shared_ptr<ALLEGRO_MOUSE_STATE> m_object;
};


} //namespace alx


#endif //ALX_MOUSESTATE_HPP
