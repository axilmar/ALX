#ifndef ALX_STATE_HPP
#define ALX_STATE_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_STATE.
 */
class State {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    State(ALLEGRO_STATE *object, bool managed = true) : m_object(object, managed ? _deleteState : [](ALLEGRO_STATE *state){}) {
    }

    /**
        Creates a keyboard state.
     */
    State() : m_object(new ALLEGRO_STATE) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Restores the state.
     */
    void restore() const {
        al_restore_state(m_object.get());
    }

    /**
        Retrieves the state.
     */
    void retrieve(int flags) {
        al_store_state(m_object.get(), flags);
    }

private:
    //allegro object
    std::shared_ptr<ALLEGRO_STATE> m_object;

    //state deleter
    static void _deleteState(ALLEGRO_STATE *state) {
        delete state;
    }
};


} //namespace alx


#endif //ALX_STATE_HPP
