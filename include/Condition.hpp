#ifndef ALX_CONDITION_HPP
#define ALX_CONDITION_HPP


#include "Mutex.hpp"
#include "Timeout.hpp"


namespace alx {


/**
    Value-based wrapper around ALLEGRO_COND.
 */
class Condition {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Condition(ALLEGRO_COND *object, bool managed = true) : m_object(object, managed ? al_destroy_cond : [](ALLEGRO_COND *){}) {
    }

    /**
        Creates a condition object.
     */
    Condition() : m_object(al_create_cond(), al_destroy_cond) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Waits for the condition to be true.
        @param mutex mutex to unlock.
     */
    void wait(Mutex &mutex) {
        al_wait_cond(m_object.get(), mutex.m_object.get());
    }

    /**
        Waits for the condition to be true until the specific time.
        @param mutex mutex to unlock.
        @param timeout timeout.
        @return true on success, false on timeout
     */
    bool wait(Mutex &mutex, const Timeout &timeout) {
        return al_wait_cond_until(m_object.get(), mutex.m_object.get(), &timeout.m_object) == 0;
    }

    /**
        Wakes all waiting threads.
     */
    void wakeAll() {
        al_broadcast_cond(m_object.get());
    }

    /**
        Wakes a random waiting thread.
     */
    void wakeOne() {
        al_signal_cond(m_object.get());
    }

private:
    //internal pointer to the allegro object
    std::shared_ptr<ALLEGRO_COND> m_object;
};


} //namespace alx


#endif //ALX_CONDITION_HPP