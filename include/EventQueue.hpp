#ifndef ALX_EVENTQUEUE_HPP
#define ALX_EVENTQUEUE_HPP


#include "EventSource.hpp"
#include "Event.hpp"


namespace alx {


/**
    Shared-based wrapper around ALLEGRO_EVENT_QUEUE.
 */
class EventQueue : public Shared<ALLEGRO_EVENT_QUEUE> {
public:
    /**
        Creates an event queue.
        @param create create flag.
     */
    EventQueue(bool create = true) : 
        Shared(create ? al_create_event_queue() : nullptr, create ? al_destroy_event_queue : [](ALLEGRO_EVENT_QUEUE *){})
    {
    }

    /**
        Checks if the queue is empty.
        @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const {
        return al_is_event_queue_empty(get());
    }

    /**
        Registers an event source.
        @param source event source.
        @return reference to this.
     */
    EventQueue& operator << (ALLEGRO_EVENT_SOURCE *source) {
        al_register_event_source(get(), source);
        return *this;
    }

    /**
        Registers an event source.
        @param source event source.
        @return reference to this.
     */
    EventQueue& operator << (const EventSource &source) {
        al_register_event_source(get(), source.get());
        return *this;
    }

    /**
        Unregisters an event source.
        @param source event source.
        @return reference to this.
     */
    EventQueue& operator >> (ALLEGRO_EVENT_SOURCE *source) {
        al_unregister_event_source(get(), source);
        return *this;
    }

    /**
        Unregisters an event source.
        @param source event source.
        @return reference to this.
     */
    EventQueue& operator >> (const EventSource &source) {
        al_unregister_event_source(get(), source.get());
        return *this;
    }

    /**
        Retrieves the next available event from the queue.
        It automatically unrefs a user event.
        @return the result event.
     */
    Event getEvent() {
        ALLEGRO_EVENT event;
        return al_get_next_event(get(), &event) ? Event(event) : Event();
    }

    /**
        Retrieves a copy of the next available event from the queue.
        It automatically unrefs a user event.
        @return the result event.
     */
    Event peekEvent() {
        ALLEGRO_EVENT event;
        return al_peek_next_event(get(), &event) ? Event(event) : Event();
    }

    /**
        Waits for an event.
        @return the next available event.
     */
    Event waitForEvent() {
        ALLEGRO_EVENT event;
        al_wait_for_event(get(), &event);
        return event;
    }

    /**
        Waits for an event.
        @param event event.
        @return reference to this.
     */
    EventQueue& operator >> (Event &event) {
        al_wait_for_event(get(), &event.get());
    }

    /**
        Waits for an event for a specific duration of time.
        @param secs seconds to wait.
        @return the next available event; if there was a timeout, the object is null.
     */
    Event waitForEvent(double secs) {
        ALLEGRO_EVENT event;
        return al_wait_for_event_timed(get(), &event, (float)secs) ? Event(event) : Event();
    }

    /**
        Waits for an event until a specific time comes.
        @param timeout specific timeoput.
        @return the next available event; if there was a timeout, the object is null.
     */
    Event waitForEvent(const ALLEGRO_TIMEOUT &timeout) {
        ALLEGRO_EVENT event;
        return al_wait_for_event_until(get(), &event, const_cast<ALLEGRO_TIMEOUT *>(&timeout)) ? Event(event) : Event();
    }

    /**
        Drops the next event.
        @return true on success.
     */
    bool dropEvent() {
        return al_drop_next_event(get());
    }

    /**
        Clears the event queue.
     */
    void clear() {
        al_flush_event_queue(get());
    }

    /**
        Constructor from external object.
        @param object object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    EventQueue(ALLEGRO_EVENT_QUEUE *object, bool managed = true) : 
        Shared(object, managed, al_destroy_event_queue, [](ALLEGRO_EVENT_QUEUE *){})
    {
    }
};


} //namespace alx


#endif //ALX_EVENTQUEUE_HPP
