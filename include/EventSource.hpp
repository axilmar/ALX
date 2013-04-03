#ifndef ALX_EVENTSOURCE_HPP
#define ALX_EVENTSOURCE_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


/**
    Wrapper class around an ALLEGRO_EVENT_SOURCE.
 */
class EventSource {
public:
    /**
        Constructor from external object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    EventSource(ALLEGRO_EVENT_SOURCE *object, bool managed = true) : m_object(object, managed ? al_destroy_user_event_source : [](ALLEGRO_EVENT_SOURCE *){}) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

private:
    //allegro object
    std::shared_ptr<ALLEGRO_EVENT_SOURCE> m_object;

    friend class EventQueue;
};


} //namespace alx


#endif //ALX_EVENTSOURCE_HPP