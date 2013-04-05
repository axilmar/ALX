#ifndef ALX_KEYBOARD_HPP
#define ALX_KEYBOARD_HPP


#include "EventSource.hpp"


namespace alx {


/**
    Keyboard functions.
 */
class Keyboard {
public:
    /**
        Returns the keyboard event source.
        @return the keyboard event source.
     */
    static EventSource getEventSource() {
        return EventSource(al_get_keyboard_event_source(), false);
    }
};


} //namespace alx



#endif //ALX_KEYBOARD_HPP
