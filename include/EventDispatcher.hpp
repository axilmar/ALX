#ifndef ALX_EVENTDISPATCHER_HPP
#define ALX_EVENTDISPATCHER_HPP


#include <unordered_map>
#include <functional>
#include "Object.hpp"
#include "Event.hpp"


namespace alx {


/**
    Base class for objects that dispatch events.
 */
class EventDispatcher : public Object {
private:
    //some required typedefs
    typedef std::function<void(Event &)> _EventHandler;
    typedef std::unordered_map<size_t, _EventHandler> _EventListenerMap;

public:
    /**
        Type of key used for removing an event listener.
     */
    class EventListenerKey {
    public:

    private:
        //internal constructor
        EventListenerKey(EventId eventId, size_t listenerId) : 
            m_eventId(eventId), m_listenerId(listenerId)
        {
        }

        EventId m_eventId;
        size_t m_listenerId;

        friend class EventDispatcher;
    };

    /**
        The default constructor.
     */
    EventDispatcher();

    /**
        Dispatches the given event to all the event handlers registered for it.
        @param event event to dispatch.
     */
    void dispatchEvent(Event &event) const;

    /**
        Dispatches the given user event wrapped up in a Event instance.
        @param event event to dispatch.
     */
    void dispatchEvent(UserEvent &event) const;

    /**
        Checks if the dispatcher as the event listener represented by the given key.
        @param key listener key as returned by 'addEventListener'.
        @return true if the dispatcher contains the event listener.
     */
    bool hasEventListener(const EventListenerKey &key) const;

    /**
        Adds the given function as an event handler to the given event type.
        @param type event type.
        @param f function to invoke when an event of this type is dispatched to this object.
        @return an event listener key which can be used to remove the event listener.
     */
    template <class T, class F> EventListenerKey addEventListener(const EventType<T> &type, F f) {
        return _addEventListener(type, std::function<void(T &)>(f));
    }

    /**
        Removes an event listener.
        @param key key.
        @return true on success.
     */
    bool removeEventListener(const EventListenerKey &key);

private:
    //some required typedefs
    typedef std::shared_ptr<_EventListenerMap> _EventListenerMapPtr;
    typedef std::unordered_map<EventId, _EventListenerMapPtr> _EventMap;

    //event map
    _EventMap m_eventMap;

    //event listener id generator
    size_t m_eventListenerId;

    //adds an event listener to the specific event map
    static EventListenerKey _addEventListenerHelper(_EventMap &eventMap, EventId eventId, const std::function<void(Event &)> &fn, size_t listenerId) {
        _EventListenerMapPtr &mapPtr = eventMap[eventId];
        if (!mapPtr) {
            mapPtr.reset(new _EventListenerMap);
        }
        (*mapPtr)[listenerId] = fn;
        return EventListenerKey(eventId, listenerId);         
    }

    //add event listener for types other than Event.
    template <class T> class _AddEventListener {
    public:
        static EventListenerKey add(_EventMap &eventMap, const EventType<T> &type, const std::function<void(T &)> &fn, size_t listenerId) {
            return _addEventListenerHelper(eventMap, type.getId(), [=](Event &event) { fn(*static_cast<T *>(event.getUserEvent())); }, listenerId);
        }
    };

    //add event listener for Event.
    template <> class _AddEventListener<Event> {
    public:
        static EventListenerKey add(_EventMap &eventMap, const EventType<Event> &type, const std::function<void(Event &)> &fn, size_t listenerId) {
            return _addEventListenerHelper(eventMap, type.getId(), fn, listenerId);
        }
    }; 

    //internal add event listener
    template <class T> EventListenerKey _addEventListener(const EventType<T> &type, const std::function<void(T &)> &fn) {
        return _AddEventListener<T>::add(m_eventMap, type, fn, ++m_eventListenerId);
    }
};


} //namespace alx


#endif //ALX_EVENTDISPATCHER_HPP
