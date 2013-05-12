#ifndef ALX_EVENTSOURCE_HPP
#define ALX_EVENTSOURCE_HPP


#include <allegro5/allegro.h>
#include "Shared.hpp"


namespace alx {


/**
    Shared-based wrapper class around an ALLEGRO_EVENT_SOURCE.
 */
class EventSource : public Shared<ALLEGRO_EVENT_SOURCE> {
    static void void_destructor(ALLEGRO_EVENT_SOURCE*) {}
public:
    /**
        Constructor from external object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    EventSource(ALLEGRO_EVENT_SOURCE *object, bool managed = true) : Shared(object, managed, al_destroy_user_event_source) {
    }

    friend class EventQueue;
};


} //namespace alx


#endif //ALX_EVENTSOURCE_HPP
