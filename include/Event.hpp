#ifndef ALX_EVENT_HPP
#define ALX_EVENT_HPP


#include <cassert>
#include "Joystick.hpp"
#include "Display.hpp"
#include "Timer.hpp"


namespace alx {


/**
    An allegro event.
 */
class Event {
public:
    /**
        default constructor.
     */
    Event() {
    }

    /**
        constructor from event struct.
     */
    Event(const ALLEGRO_EVENT &event) :m_object(event) {
    }

    /**
        If the event is a user event, then it is automatically unrefd.
     */
    ~Event() {
        if (_isUserEvent(m_object.type)) al_unref_user_event(&m_object.user);
    }

    /**
        Returns true if the event is a user one.
        @return true if user event, false otherwise.
     */
    bool isUserEvent() const {
        return _isUserEvent(m_object.type);
    }

    int getType() const {
        return m_object.type;
    }

    EventSource getEventSource() const {
        return EventSource(m_object.any.source, false);
    }

    double getTimestamp() const {
        return m_object.any.timestamp;
    }

    Display getDisplay() const {
        return Display(m_object.display.source, false);
    }

    int getDisplayX() const {
        return m_object.display.x;
    }

    int getDisplayY() const {
        return m_object.display.y;
    }

    int getDisplayWidth() const {
        return m_object.display.width;
    }

    int getDisplayHeight() const {
        return m_object.display.height;
    }

    int getDisplayOrientation() const {
        return m_object.display.orientation;
    }

    Joystick getJoystick() const {
        return Joystick(m_object.joystick.source, false);
    }

    Joystick getJoystickId() const {
        return Joystick(m_object.joystick.id, false);
    }

    int getJoystickStick() const {
        return m_object.joystick.stick;
    }

    int getJoystickAxis() const {
        return m_object.joystick.axis;
    }

    float getJoystickPos() const {
        return m_object.joystick.pos;
    }

    int getJoystickButton() const {
        return m_object.joystick.button;
    }

    Display getKeyboardDisplay() const {
        return Display(m_object.keyboard.display, false);
    }

    int getKeyboardKeycode() const {
        return m_object.keyboard.keycode;
    }

    int getKeyboardUnicodeCharacter() const {
        return m_object.keyboard.unichar;
    }

    int getKeyboardModifiers() const {
        return m_object.keyboard.modifiers;
    }

    bool getKeyboardRepeat() const {
        return m_object.keyboard.repeat;
    }

    Display getMouseDisplay() const {
        return Display(m_object.mouse.display, false);
    }

    int getMouseX() const {
        return m_object.mouse.x;
    }

    int getMouseY() const {
        return m_object.mouse.y;
    }

    int getMouseZ() const {
        return m_object.mouse.z;
    }

    int getMouseW() const {
        return m_object.mouse.w;
    }

    int getMouseDX() const {
        return m_object.mouse.dx;
    }

    int getMouseDY() const {
        return m_object.mouse.dy;
    }

    int getMouseDZ() const {
        return m_object.mouse.dz;
    }

    int getMouseDW() const {
        return m_object.mouse.dw;
    }

    float getMousePressure() const {
        return m_object.mouse.pressure;
    }

    Timer getTimer() const {
        return Timer(m_object.timer.source, false);
    }

    int64_t getTimerCount() const {
        return m_object.timer.count;
    }

    double getTimerError() const {
        return m_object.timer.error;
    }

    intptr_t getUserData1() const {
        return m_object.user.data1;
    }

    intptr_t getUserData2() const {
        return m_object.user.data2;
    }

    intptr_t getUserData3() const {
        return m_object.user.data3;
    }

    intptr_t getUserData4() const {
        return m_object.user.data4;
    }

private:
    //allegro event
    ALLEGRO_EVENT m_object;

    friend class UserEventSource;
    
    //check if the type represents an Allegro event or a user type event.
    static bool _isUserEvent(int type);
};


} //namespace alx


#endif //ALX_EVENT_HPP
