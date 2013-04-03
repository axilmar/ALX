#ifndef ALX_IEVENTSOURCE_HPP
#define ALX_IEVENTSOURCE_HPP


#include "EventSource.hpp"


namespace alx {


/**
    Interface for event source classes.
 */
class IEventSource {
public:
    /**
        Retrieves the event source for the object.
        @return the event source for the object.
     */
    virtual EventSource getEventSource() const = 0;
};


} //namespace alx


#endif //ALX_IEVENTSOURCE_HPP
