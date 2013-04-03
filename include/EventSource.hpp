#ifndef ALX_EVENTSOURCE_HPP
#define ALX_EVENTSOURCE_HPP


#include <memory>
#include <allegro5/allegro.h>


namespace alx {


//TODO


class EventSource {
public:
    EventSource(ALLEGRO_EVENT_SOURCE *object, bool managed = true) : m_object(object, managed ? al_destroy_user_event_source : [](ALLEGRO_EVENT_SOURCE *){}) {
    }

private:
    std::shared_ptr<ALLEGRO_EVENT_SOURCE> m_object;
};


} //namespace alx


#endif //ALX_EVENTSOURCE_HPP