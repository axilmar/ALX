#ifndef ALX_MUTEX_HPP
#define ALX_MUTEX_HPP


#include <allegro5/allegro.h>
#include "Lock.hpp"
#include "Shared.hpp"


namespace alx {


/**
    Shared-based wrapper class around ALLEGRO_MUTEX.
 */
class Mutex : public Shared<ALLEGRO_MUTEX> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Mutex(ALLEGRO_MUTEX *object, bool managed = true) : Shared(object, managed, al_destroy_mutex, [](ALLEGRO_MUTEX *){}) {
    }

    /**
        Creates a mutex.
        @param recursive if true, a recursive mutex is created.
     */
    Mutex(bool recursive = false) : Shared(recursive ? al_create_mutex_recursive() : al_create_mutex(), al_destroy_mutex) {
    }

    /**
        locks the mutex.
     */
    void lock() {
        al_lock_mutex(get());
    }

    /**
        unlocks the mutex.
     */
    void unlock() {
        al_unlock_mutex(get());
    }

    /**
        Runs the given code with the mutex locked for the duration of the call.
        The function is exception-safe: if an exception is thrown, the mutex will be unlocked appropriately.
        @param f function to execute with the mutex.
        @return whatever the function returns.
     */
    template <class F> auto operator << (F f) -> decltype(f()) {
        Lock<Mutex> lock(*this);
        return f();
    }
};


} //namespace alx



#endif //ALX_MUTEX_HPP
