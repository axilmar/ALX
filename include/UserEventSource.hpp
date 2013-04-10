#ifndef ALX_USER_EVENT_SOURCE_HPP
#define ALX_USER_EVENT_SOURCE_HPP


#include "EventSource.hpp"


namespace alx {


/**
    Base class for user event sources.
 */
class UserEventSource {
public:
    /**
        The default constructor.
        Initializes an internal user event source structure.
     */
    UserEventSource() {
        al_init_user_event_source(&m_event_source);
    }

    /**
        Destroys the internal user event source.
     */
    virtual ~UserEventSource() {
        al_destroy_user_event_source(&m_event_source);
    }

    /**
        Retrieves the event source for the object.
        @return the event source for the object.
     */
    EventSource getEventSource() const {
        return EventSource(const_cast<ALLEGRO_EVENT_SOURCE *>(&m_event_source), false);
    }

    /**
        Retrieves the event source for the object.
        @return the event source for the object.
     */
    operator EventSource () const {
        return EventSource(const_cast<ALLEGRO_EVENT_SOURCE *>(&m_event_source), false);
    }

    /**
        emits a user event.
        @param event event to emit.
        @param dtor destructor.
        @return true on success.
     */
    bool emitUserEvent(const ALLEGRO_EVENT &event, void (*dtor)(ALLEGRO_USER_EVENT *) = nullptr) {
        return al_emit_user_event(&m_event_source, const_cast<ALLEGRO_EVENT *>(&event), dtor);
    }

    /**
        emits a user event.
        @param event event to emit.
        @param dtor destructor.
        @return true on success.
     */
    bool emitUserEvent(const Event &event, void (*dtor)(ALLEGRO_USER_EVENT *) = nullptr) {
        return al_emit_user_event(&m_event_source, const_cast<ALLEGRO_EVENT *>(&event.get()), dtor);
    }

    /**
        Emits a user event.
        It copies the user event pointer to the field ALLEGRO_EVENT.user.data1, and uses an internal destructor which deletes the object.
        The Event class will automatically unref the object, which will cause the destructor to be invoked.
        The type of the user event is copied to ALLEGRO_EVENT.type.
        @param event user event.

     */
    bool emitUserEvent(UserEvent *userEvent) {
        ALLEGRO_EVENT event;
        event.user.type = userEvent->getType();
        event.user.data1 = (intptr_t)userEvent;
        return al_emit_user_event(&m_event_source, &event, &_userEventDestructor);
    }

private:
    //the internal allegro event source object
    ALLEGRO_EVENT_SOURCE m_event_source;

    //user event destructor
    static void _userEventDestructor(ALLEGRO_USER_EVENT *event) {
        delete reinterpret_cast<UserEvent *>(event->data1);
    }
};


} //namespace alx


#endif //ALX_USER_EVENT_SOURCE_HPP
