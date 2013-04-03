#ifndef ALX_USEREVENT_HPP
#define ALX_USEREVENT_HPP


namespace alx {


/**
    Base class for user events.
 */
class UserEvent {
public:
    /**
        constructor.
        @param type type.
     */
    UserEvent(int type) : m_type(type) {
    }

    /**
        destructor.
     */
    virtual ~UserEvent() {
    }

    /**
        Returns the type of event.
        @return the type of event.
     */
    int getType() const {
        return m_type;
    }

private:
    //type
    int m_type;
};


} //namespace alx


#endif //ALX_USEREVENT_HPP
