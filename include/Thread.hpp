#ifndef ALX_THREAD_HPP
#define ALX_THREAD_HPP


#include <functional>
#include <allegro5/allegro.h>
#include "Shared.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_THREAD.
 */
class Thread : public Shared<ALLEGRO_THREAD> {
public:
    /**
        Function object type.
     */
    typedef std::function<void*()> Function;

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Thread(ALLEGRO_THREAD *object, bool managed = true) : Shared(object, managed, al_destroy_thread, [](ALLEGRO_THREAD *){}) {
    }

    /**
        Creates an Allegro thread.
        @param proc procedure.
        @param arg argument.
     */
    Thread(void *(*proc)(ALLEGRO_THREAD *, void *), void *arg) : Shared(al_create_thread(proc, arg), al_destroy_thread) {
    }

    /**
        Creates a thread that runs the specific function object.
        @param f function object to run in a separate thread.
     */
    Thread(const Function &f) :  Shared(al_create_thread(&_run, new Function(f)), al_destroy_thread) {
    }

    /**
        returns the stop flag.
        @return the stop flag.
     */
    bool getStop() const {
        return al_get_thread_should_stop(get());
    }

    /**
        Set the stop flag.
     */
    void setStop() {
        al_set_thread_should_stop(get());
    }

    /**
        Wait for thread to terminate.
        @return result of thread.
     */
    void *wait() {
        void *result;
        al_join_thread(get(), &result);
        return result;
    }

    /**
        starts the thread.
     */
    void start() {
        al_start_thread(get());
    }

    /**
        Sets the stop flag, then waits for termination.
        @param result thread result variable.
        @return result of thread.
     */
    void *stop() {
        setStop();
        return wait();
    }

private:
    //std function runner
    static void *_run(ALLEGRO_THREAD *thread, void *arg) {
        std::shared_ptr<Function> funcPtr(reinterpret_cast<Function *>(arg));
        return funcPtr->operator ()();
    }
};


} //namespace alx


#endif //ALX_THREAD_HPP
