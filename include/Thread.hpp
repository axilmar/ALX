#ifndef ALX_THREAD_HPP
#define ALX_THREAD_HPP


#include <memory>
#include <functional>
#include <allegro5/allegro.h>


namespace alx {


/**
    Value-based wrapper around ALLEGRO_THREAD.
 */
class Thread {
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
    Thread(ALLEGRO_THREAD *object, bool managed = true) : m_object(object, managed ? al_destroy_thread : [](ALLEGRO_THREAD *){}) {
    }

    /**
        Creates an Allegro thread.
        @param proc procedure.
        @param arg argument.
     */
    Thread(void *(*proc)(ALLEGRO_THREAD *, void *), void *arg) : m_object(al_create_thread(proc, arg), al_destroy_thread) {
    }

    /**
        Creates a thread that runs the specific function object.
        @param f function object to run in a separate thread.
     */
    Thread(const Function &f) :  m_object(al_create_thread(&_run, new Function(f)), al_destroy_thread) {
    }

    /**
        returns the stop flag.
        @return the stop flag.
     */
    bool getStop() const {
        return al_get_thread_should_stop(m_object.get());
    }

    /**
        Set the stop flag.
     */
    void setStop() {
        al_set_thread_should_stop(m_object.get());
    }

    /**
        Wait for thread to terminate.
        @return result of thread.
     */
    void *wait() {
        void *result;
        al_join_thread(m_object.get(), &result);
        return result;
    }

    /**
        starts the thread.
     */
    void start() {
        al_start_thread(m_object.get());
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
    //allegro object
    std::shared_ptr<ALLEGRO_THREAD> m_object;

    //std function runner
    static void *_run(ALLEGRO_THREAD *thread, void *arg) {
        std::shared_ptr<Function> funcPtr(reinterpret_cast<Function *>(arg));
        return funcPtr->operator ()();
    }
};


} //namespace alx


#endif //ALX_THREAD_HPP
