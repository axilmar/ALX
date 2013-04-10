#ifndef ALX_CONDITION_HPP
#define ALX_CONDITION_HPP


#include "Mutex.hpp"
#include "Timeout.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_COND.
 */
class Condition : public Shared<ALLEGRO_COND> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Condition(ALLEGRO_COND *object, bool managed = true) : Shared(object, managed, al_destroy_cond, [](ALLEGRO_COND *){}) {
    }

    /**
        Creates a condition object.
        @param create create flag.
     */
    Condition(bool create = true) : Shared(create ? al_create_cond() : nullptr, al_destroy_cond) {
    }

    /**
        Waits for the condition to be true.
        @param mutex mutex to unlock.
     */
    void wait(Mutex &mutex) {
        al_wait_cond(get(), mutex.get());
    }

    /**
        Waits for the condition to be true until the specific time.
        @param mutex mutex to unlock.
        @param timeout timeout.
        @return true on success, false on timeout
     */
    bool wait(Mutex &mutex, const Timeout &timeout) {
        return al_wait_cond_until(get(), mutex.get(), &timeout.get()) == 0;
    }

    /**
        Wakes all waiting threads.
     */
    void wakeAll() {
        al_broadcast_cond(get());
    }

    /**
        Wakes a random waiting thread.
     */
    void wakeOne() {
        al_signal_cond(get());
    }
};


} //namespace alx


#endif //ALX_CONDITION_HPP