#ifndef ALX_MOUSE_HPP
#define ALX_MOUSE_HPP


#include "EventSource.hpp"


namespace alx {


/**
    Mouse functions.
 */
class Mouse {
public:
    /**
        Returns the mouse event source.
        @return the mouse event source.
     */
    static EventSource getEventSource() {
        return EventSource(al_get_mouse_event_source(), false);
    }
};


} //namespace alx


#endif //ALX_MOUSE_HPP
