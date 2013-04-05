#ifndef ALX_MUTEX_HPP
#define ALX_MUTEX_HPP


#include <memory>
#include <allegro5/allegro.h>
#include "Lock.hpp"


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_MUTEX.
 */
class Mutex {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Mutex(ALLEGRO_MUTEX *object, bool managed = true) : m_object(object, managed ? al_destroy_mutex : [](ALLEGRO_MUTEX *){}) {
    }

    /**
        Creates a mutex.
        @param recursive if true, a recursive mutex is created.
     */
    Mutex(bool recursive = false) : m_object(recursive ? al_create_mutex_recursive() : al_create_mutex(), al_destroy_mutex) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        locks the mutex.
     */
    void lock() {
        al_lock_mutex(m_object.get());
    }

    /**
        unlocks the mutex.
     */
    void unlock() {
        al_unlock_mutex(m_object.get());
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

private:
    std::shared_ptr<ALLEGRO_MUTEX> m_object;

    friend class Condition;
};


} //namespace alx



#endif //ALX_MUTEX_HPP
