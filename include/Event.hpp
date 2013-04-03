#ifndef ALX_EVENT_HPP
#define ALX_EVENT_HPP


#include <cassert>
#include <memory>
#include <allegro5/allegro.h>


namespace alx {


/**
    Value-based wrapper around ALLEGRO_EVENT.
    On destruction, if the event is of user type, then it is automatically unreferenced.
 */
class Event {
public:
    /**
        constructor from external object.
        @param event event.
     */
    Event(const ALLEGRO_EVENT &event) : m_object(new ALLEGRO_EVENT(event), _deleteEvent) {
    }

    /**
        null event constructor.
     */
    Event() {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Returns true if the event is a user one.
        @return true if user event, false otherwise.
     */
    bool isUserEvent() const {
        return m_object ? _isUserEvent(m_object->type) : false;
    }

    /**
        Returns the underlying event structure.
        @return the underlying event structure.
     */
    const ALLEGRO_EVENT &getEvent() const {
        assert(m_object);
        return *m_object.get();
    }

private:
    //Allegro object
    std::shared_ptr<ALLEGRO_EVENT> m_object;

    friend class UserEventSource;
    
    //check if the type represents an Allegro event or a user type event.
    static bool _isUserEvent(int type);

    //deletes the given event, and also unrefs it if it is a user event
    static void _deleteEvent(ALLEGRO_EVENT *event);
};


} //namespace alx


#endif //ALX_EVENT_HPP
