#ifndef ALX_EVENTTYPE_HPP
#define ALX_EVENTTYPE_HPP


namespace alx {


/**
    Event id.
 */
typedef const char *EventId;


/**
    A static event type descriptor.
    @param T event type class passed to the function.
 */
template <class T> class EventType {
public:
    /**
        Type of event parameter.
     */
    typedef T ParameterType;

    /**
        constructor.
        @param id event id.
     */
    EventType(EventId id) : m_id(id) {
    }

    /**
        Returns the event id.
        @return the event id.
     */
    EventId getId() const {
        return m_id;
    }

private:
    EventId m_id;
};


} //namespace alx


#endif //ALX_EVENTTYPE_HPP
