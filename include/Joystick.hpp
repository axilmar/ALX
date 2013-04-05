#ifndef ALX_JOYSTICK_HPP
#define ALX_JOYSTICK_HPP


#include "String.hpp"
#include "EventSource.hpp"
#include "JoystickState.hpp"


namespace alx {


/**
    Value-based wrapper class around ALLEGRO_JOYSTICK.
 */
class Joystick {
public:
    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Joystick(ALLEGRO_JOYSTICK *object, bool managed = true) : m_object(object, managed ? al_release_joystick : [](ALLEGRO_JOYSTICK *){}) {
    }

    /**
        Gets a joystick.
        @param num joystick number.
     */
    Joystick(int num) : m_object(al_get_joystick(num), al_release_joystick) {
    }

    /**
        Checks if the internal allegro object is null.
        @return true if null, false otherwise.
     */
    bool isNull() const {
        return m_object;
    }

    /**
        Checks if a joystick is active.
        @return true if active.
     */
    bool isActive() const {
        return al_get_joystick_active(m_object.get());
    }

    /**
        Returns the joystick's name.
        @return the joystick's name.
     */
    String getName() const {
        return al_get_joystick_name(m_object.get());
    }

    /**
        Returns the given stick's name.
        @param stick stick index.
        @return the given stick's name.
     */
    String getStickName(int stick) const {
        return al_get_joystick_stick_name(m_object.get(), stick);
    }

    /**
        Returns the given axis' name.
        @param stick stick index.
        @param axis axis index.
        @return the given stick axis' name.
     */
    String getAxisName(int stick, int axis) const {
        return al_get_joystick_axis_name(m_object.get(), stick, axis);
    }

    /**
        Returns the given button's name.
        @param button button index.
        @return the given button's name.
     */
    String getButtonName(int button) const {
        return al_get_joystick_button_name(m_object.get(), button);
    }

    /**
        Returns the given stick's flags.
        @param stick stick index.
        @return the given stick's flags.
     */
    int getStickFlags(int stick) const {
        return al_get_joystick_stick_flags(m_object.get(), stick);
    }

    /**
        Returns the joystick's number of sticks.
        @return the joystick's number of sticks.
     */
    int getNumSticks() const {
        return al_get_joystick_num_sticks(m_object.get());
    }

    /**
        Returns the joystick's number of axes.
        @return the joystick's number of axes.
     */
    int getNumAxes() const {
        return al_get_joystick_num_axes(m_object.get());
    }

    /**
        Returns the joystick's number of buttons.
        @return the joystick's number of buttons.
     */
    int getNumButtons() const {
        return al_get_joystick_num_buttons(m_object.get());
    }

    /**
        Returns the joystick's state this particular instance.
        @return the joystick's state this particular instance.
     */
    JoystickState getState() const {
        JoystickState state;
        al_get_joystick_state(m_object.get(), state.m_object.get());
        return state;
    }

    /**
        Returns the joystick event source.
        @return the joystick event source.
     */
    static EventSource getEventSource() {
        return EventSource(al_get_joystick_event_source(), false);
    }

private:
    //allegro object
    std::shared_ptr<ALLEGRO_JOYSTICK> m_object;
};


} //namespace alx


#endif //ALX_JOYSTICK_HPP
