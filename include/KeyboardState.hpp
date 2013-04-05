#ifndef ALX_KEYBOARDSTATE_HPP
#define ALX_KEYBOARDSTATE_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_KEYBOARD_STATE.
 */
class KeyboardState {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    KeyboardState(ALLEGRO_KEYBOARD_STATE *object, bool managed = true) : m_object(object, managed ? [](ALLEGRO_KEYBOARD_STATE *state){ delete state; } : [](ALLEGRO_KEYBOARD_STATE *state){}) {
    }

    /**
        Creates a keyboard state.
     */
    KeyboardState() : m_object(new ALLEGRO_KEYBOARD_STATE) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        puts the keyboard state into this object.
     */
    void getKeyboardState() const {
        al_get_keyboard_state(m_object.get());
    }

    /**
        Checks if a key was down in this state.
        @param keycode key code.
        @return true if the key was down.
     */
    bool isKeyDown(int keycode) const {
        return al_key_down(m_object.get());
    }

private:
    //allegro object
    std::shared_ptr<ALLEGRO_KEYBOARD_STATE> m_object;
};


} //namespace alx


#endif //ALX_KEYBOARDSTATE_HPP
