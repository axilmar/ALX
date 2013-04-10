#include "EventDispatcher.hpp"


namespace alx {


//return event type from allegro event type
const EventType<Event> *_allegroEventType(int type) {
    switch (type) {
        case ALLEGRO_EVENT_JOYSTICK_AXIS         : return &Event::JOYSTICK_AXIS         ;
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN  : return &Event::JOYSTICK_BUTTON_DOWN  ;
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP    : return &Event::JOYSTICK_BUTTON_UP    ;
        case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION: return &Event::JOYSTICK_CONFIGURATION;
        case ALLEGRO_EVENT_KEY_DOWN              : return &Event::KEY_DOWN              ;
        case ALLEGRO_EVENT_KEY_CHAR              : return &Event::KEY_CHAR              ;
        case ALLEGRO_EVENT_KEY_UP                : return &Event::KEY_UP                ;
        case ALLEGRO_EVENT_MOUSE_AXES            : return &Event::MOUSE_AXES            ;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN     : return &Event::MOUSE_BUTTON_DOWN     ;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP       : return &Event::MOUSE_BUTTON_UP       ;
        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY   : return &Event::MOUSE_ENTER_DISPLAY   ;
        case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY   : return &Event::MOUSE_LEAVE_DISPLAY   ;
        case ALLEGRO_EVENT_MOUSE_WARPED          : return &Event::MOUSE_WARPED          ;
        case ALLEGRO_EVENT_TIMER                 : return &Event::TIMER                 ;
        case ALLEGRO_EVENT_DISPLAY_EXPOSE        : return &Event::DISPLAY_EXPOSE        ;
        case ALLEGRO_EVENT_DISPLAY_RESIZE        : return &Event::DISPLAY_RESIZE        ;
        case ALLEGRO_EVENT_DISPLAY_CLOSE         : return &Event::DISPLAY_CLOSE         ;
        case ALLEGRO_EVENT_DISPLAY_LOST          : return &Event::DISPLAY_LOST          ;
        case ALLEGRO_EVENT_DISPLAY_FOUND         : return &Event::DISPLAY_FOUND         ;
        case ALLEGRO_EVENT_DISPLAY_SWITCH_IN     : return &Event::DISPLAY_SWITCH_IN     ;
        case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT    : return &Event::DISPLAY_SWITCH_OUT    ;
        case ALLEGRO_EVENT_DISPLAY_ORIENTATION   : return &Event::DISPLAY_ORIENTATION   ;
        case ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE   : return &Event::NATIVE_DIALOG_CLOSE   ;
    }
    return nullptr;
}


//the default constructor.
EventDispatcher::EventDispatcher() : 
    m_eventListenerId(-1)
{
}


//dispatches the given event
void EventDispatcher::dispatchEvent(Event &event) const {
    //get the event type, depending on the allegro event
    const EventType<Event> *eventType = _allegroEventType(event.getType());

    //either get the event type from the allegro event or the user event
    EventId id = eventType ? eventType->getId() : event.getUserEvent()->getId();

    //find the event listener map
    _EventMap::const_iterator it = m_eventMap.find(id);
    if (it == m_eventMap.end()) return;

    //invoke all handlers
    _EventListenerMap &map = *it->second;
    for(auto &handler : map) {
        handler.second(event);
    }
}


//dispatches a user event.
void EventDispatcher::dispatchEvent(UserEvent &event) {
    
}


//checks if the dispatcher has an event listener.
bool EventDispatcher::hasEventListener(const EventListenerKey &key) const {
    //find the event listener map
    _EventMap::const_iterator it = m_eventMap.find(key.m_eventId);
    if (it == m_eventMap.end()) return false;

    //find the event listener map
    _EventListenerMap::iterator it1 = it->second->find(key.m_listenerId);
    if (it1 == it->second->end()) return false;

    //success
    return true;
}


//removes an event listener
bool EventDispatcher::removeEventListener(const EventListenerKey &key) {
    //find the event listener map
    _EventMap::const_iterator it = m_eventMap.find(key.m_eventId);
    if (it == m_eventMap.end()) return false;

    //find the event listener map
    _EventListenerMap::iterator it1 = it->second->find(key.m_listenerId);
    if (it1 == it->second->end()) return false;

    //remove the entry from the event listener map
    it->second->erase(it1);
    return true;
}


} //namespace alx
