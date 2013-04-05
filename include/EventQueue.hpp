#ifndef ALX_EVENTQUEUE_HPP
#define ALX_EVENTQUEUE_HPP


#include "EventSource.hpp"
#include "Event.hpp"


namespace alx {


/**
    Value-based wrapper around ALLEGRO_EVENT_QUEUE.
 */
class EventQueue {
public:
    /**
        Constructor from external object.
        @param object object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    EventQueue(ALLEGRO_EVENT_QUEUE *object, bool managed = true) : m_object(object, managed ? al_destroy_event_queue : [](ALLEGRO_EVENT_QUEUE *){}) {
    }

    /**
        Creates an event queue.
     */
    EventQueue() : m_object(al_create_event_queue(), al_destroy_event_queue) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Registers an event source.
        @param source event source.
        @return reference to this.
     */
    EventQueue& operator << (ALLEGRO_EVENT_SOURCE *source) {
        al_register_event_source(m_object.get(), source);
        return *this;
    }

    /**
        Registers an event source.
        @param source event source.
        @return reference to this.
     */
    template <class T> EventQueue& operator << (const T &source) {
        al_register_event_source(m_object.get(), source.getEventSource().m_object.get());
        return *this;
    }

    /**
        Unregisters an event source.
        @param source event source.
        @return reference to this.
     */
    EventQueue& operator >> (ALLEGRO_EVENT_SOURCE *source) {
        al_unregister_event_source(m_object.get(), source);
        return *this;
    }

    /**
        Unregisters an event source.
        @param source event source.
        @return reference to this.
     */
    template <class T> EventQueue& operator >> (const T &source) {
        al_unregister_event_source(m_object.get(), source.getEventSource().m_object.get());
        return *this;
    }

    /**
        Checks if the queue is empty.
        @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const {
        return al_is_event_queue_empty(m_object.get());
    }

    /**
        Retrieves the next available event from the queue.
        It automatically unrefs a user event.
        @return the result event.
     */
    Event getEvent() {
        ALLEGRO_EVENT event;
        return al_get_next_event(m_object.get(), &event) ? Event(event) : Event();
    }

    /**
        Retrieves a copy of the next available event from the queue.
        It automatically unrefs a user event.
        @return the result event.
     */
    Event peekEvent() {
        ALLEGRO_EVENT event;
        return al_peek_next_event(m_object.get(), &event) ? Event(event) : Event();
    }

    /**
        Waits for an event.
        @return the next available event.
     */
    Event waitForEvent() {
        ALLEGRO_EVENT event;
        al_wait_for_event(m_object.get(), &event);
        return event;
    }

    /**
        Waits for an event for a specific duration of time.
        @param secs seconds to wait.
        @return the next available event; if there was a timeout, the object is null.
     */
    Event waitForEvent(double secs) {
        ALLEGRO_EVENT event;
        return al_wait_for_event_timed(m_object.get(), &event, (float)secs) ? Event(event) : Event();
    }

    /**
        Waits for an event until a specific time comes.
        @param timeout specific timeoput.
        @return the next available event; if there was a timeout, the object is null.
     */
    Event waitForEvent(const ALLEGRO_TIMEOUT &timeout) {
        ALLEGRO_EVENT event;
        return al_wait_for_event_until(m_object.get(), &event, const_cast<ALLEGRO_TIMEOUT *>(&timeout)) ? Event(event) : Event();
    }

    /**
        Drops the next event.
        @return true on success.
     */
    bool dropEvent() {
        return al_drop_next_event(m_object.get());
    }

    /**
        Clears the event queue.
     */
    void clear() {
        al_flush_event_queue(m_object.get());
    }

private:
    std::shared_ptr<ALLEGRO_EVENT_QUEUE> m_object;
};


} //namespace alx


#endif //ALX_EVENTQUEUE_HPP
