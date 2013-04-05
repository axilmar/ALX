#ifndef ALX_TIMER_HPP
#define ALX_TIMER_HPP


#include "EventSource.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_TIMER.
 */
class Timer : public Shared<ALLEGRO_TIMER> {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Timer(ALLEGRO_TIMER *object, bool managed = true) : Shared(object, managed, al_destroy_timer, [](ALLEGRO_TIMER *){}) {
    }

    /**
        Creates a timer.
        @param speedSecs speed, in seconds.
     */
    Timer(double speedSecs) : Shared(al_create_timer(speedSecs), al_destroy_timer) {
    }

    /**
        Checks if the timer is started.
        @return true if started.
     */
    bool isStarted() const {
        return al_get_timer_started(get());
    }

    /**
        Returns the timer count.
        @return the timer count.
     */
    int64_t getCount() const {
        return al_get_timer_count(get());
    }

    /**
        Returns the timer speed.
        @return the timer speed in seconds.
     */
    double getSpeed() const {
        return al_get_timer_speed(get());
    }

    /**
        Returns the event source of the timer.
        @return the event source of the timer.
     */
    EventSource getEventSource() const {
        return al_get_timer_event_source(get());
    }

    /**
        Start the timer.
     */
    void start() {
        al_start_timer(get());
    }

    /**
        Stops the timer.
     */
    void stop() {
        al_stop_timer(get());
    }

    /**
        Sets the timer count.
        @param count new count.
     */
    void setCount(int64_t count) {
        al_set_timer_count(get(), count);
    }

    /**
        Adds the given count to the timer.
        @param count count to add.
     */
    void addCount(int64_t count) {
        al_add_timer_count(get(), count);
    }

    /**
        Sets the timer speed.
        @param speedSecs the timer speed, in seconds.
     */
    void setSpeed(double speedSecs) {
        al_set_timer_speed(get(), speedSecs);
    }
};


} //namespace alx


#endif //ALX_TIMER_HPP
