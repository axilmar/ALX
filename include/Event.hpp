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

    /**
        Returns the type of the event.
        @return the type of the event.
     */
    int getType() const {
        return m_object.type;
    }

    /**
        Returns the event source.
        @return the event source.
     */
    EventSource getEventSource() const {
        return EventSource(m_object.any.source, false);
    }

    /**
        Returns the timestamp.
        @return the timestamp.
     */
    double getTimestamp() const {
        return m_object.any.timestamp;
    }

    /**
        Returns the display.
        @return the display.
     */
    Display getDisplay() const {
        return Display(m_object.display.source, false);
    }

    /**
        Returns the display x.
        @return the display x.
     */
    int getDisplayX() const {
        return m_object.display.x;
    }

    /**
        Returns the display y.
        @return the display y.
     */
    int getDisplayY() const {
        return m_object.display.y;
    }

    /**
        Returns the display width.
        @return the display width.
     */
    int getDisplayWidth() const {
        return m_object.display.width;
    }

    /**
        Returns the display height.
        @return the display height.
     */
    int getDisplayHeight() const {
        return m_object.display.height;
    }

    /**
        Returns the display orientation.
        @return the display orientation.
     */
    int getDisplayOrientation() const {
        return m_object.display.orientation;
    }

    /**
        Returns the joystick.
        @return the joystick.
     */
    Joystick getJoystick() const {
        return Joystick(m_object.joystick.source, false);
    }

    /**
        Returns the joystick id.
        @return the joystick id.
     */
    Joystick getJoystickId() const {
        return Joystick(m_object.joystick.id, false);
    }

    /**
        Returns the joystick stick.
        @return the joystick stick.
     */
    int getJoystickStick() const {
        return m_object.joystick.stick;
    }

    /**
        Returns the joystick axis.
        @return the joystick axis.
     */
    int getJoystickAxis() const {
        return m_object.joystick.axis;
    }

    /**
        Returns the joystick position.
        @return the joystick position.
     */
    float getJoystickPos() const {
        return m_object.joystick.pos;
    }

    /**
        Returns the joystick button.
        @return the joystick button.
     */
    int getJoystickButton() const {
        return m_object.joystick.button;
    }

    /**
        Returns the keyboard display.
        @return the keyboard display.
     */
    Display getKeyboardDisplay() const {
        return Display(m_object.keyboard.display, false);
    }

    /**
        Returns the keyboard keycode.
        @return the keyboard keycode.
     */
    int getKeyboardKeycode() const {
        return m_object.keyboard.keycode;
    }

    /**
        Returns the keyboard unicode character.
        @return the keyboard unicode character.
     */
    int getKeyboardCharacter() const {
        return m_object.keyboard.unichar;
    }

    /**
        Returns the keyboard modifiers.
        @return the keyboard modifiers.
     */
    int getKeyboardModifiers() const {
        return m_object.keyboard.modifiers;
    }

    /**
        Returns the keyboard repeat flag.
        @return the keyboard repeat flag.
     */
    bool getKeyboardRepeat() const {
        return m_object.keyboard.repeat;
    }

    /**
        Returns the mouse display.
        @return the mouse display.
     */
    Display getMouseDisplay() const {
        return Display(m_object.mouse.display, false);
    }

    /**
        Returns the mouse x.
        @return the mouse x.
     */
    int getMouseX() const {
        return m_object.mouse.x;
    }

    /**
        Returns the mouse y.
        @return the mouse y.
     */
    int getMouseY() const {
        return m_object.mouse.y;
    }

    /**
        Returns the mouse z.
        @return the mouse z. 
     */
    int getMouseZ() const {
        return m_object.mouse.z;
    }

    /**
        Returns the mouse w.
        @return the mouse w. 
     */
    int getMouseW() const {
        return m_object.mouse.w;
    }

    /**
        Returns the mouse dx.
        @return the mouse dx. 
     */
    int getMouseDX() const {
        return m_object.mouse.dx;
    }

    /**
        Returns the mouse dy.
        @return the mouse dy. 
     */
    int getMouseDY() const {
        return m_object.mouse.dy;
    }

    /**
        Returns the mouse dz.
        @return the mouse dz. 
     */
    int getMouseDZ() const {
        return m_object.mouse.dz;
    }

    /**
        Returns the mouse dw.
        @return the mouse dw. 
     */
    int getMouseDW() const {
        return m_object.mouse.dw;
    }

    /**
        Returns the mouse pressure.
        @return the mouse pressure. 
     */
    float getMousePressure() const {
        return m_object.mouse.pressure;
    }

    /**
        Returns the timer.
        @return the timer.
     */
    Timer getTimer() const {
        return Timer(m_object.timer.source, false);
    }

    /**
        Returns the timer count.
        @return the timer count.
     */
    int64_t getTimerCount() const {
        return m_object.timer.count;
    }

    /**
        Returns the timer error.
        @return the timer error.
     */
    double getTimerError() const {
        return m_object.timer.error;
    }

    /**
        Returns the user data field 1.
        @return the user data field 1.
     */
    intptr_t getUserData1() const {
        return m_object.user.data1;
    }

    /**
        Returns the user data field 2.
        @return the user data field 2. 
     */
    intptr_t getUserData2() const {
        return m_object.user.data2;
    }

    /**
        Returns the user data field 3.
        @return the user data field 3. 
     */
    intptr_t getUserData3() const {
        return m_object.user.data3;
    }

    /**
        Returns the user data field 4.
        @return the user data field 4. 
     */
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
