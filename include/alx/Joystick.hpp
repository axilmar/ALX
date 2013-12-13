#ifndef ALX_JOYSTICK_HPP
#define ALX_JOYSTICK_HPP


#include "alx/String.hpp"
#include "alx/EventSource.hpp"


namespace alx {


/**
    Shared-based wrapper class around ALLEGRO_JOYSTICK.
 */
class Joystick : public Shared<ALLEGRO_JOYSTICK> {
public:
    /**
        Null constructor.
     */
    Joystick() {
    }

    /**
        Gets a joystick.
        @param num joystick number.
     */
    Joystick(int num) : Shared(al_get_joystick(num), al_release_joystick) {
    }

    /**
        Checks if a joystick is active.
        @return true if active.
     */
    bool isActive() const {
        return al_get_joystick_active(get());
    }

    /**
        Returns the joystick's name.
        @return the joystick's name.
     */
    String getName() const {
        return al_get_joystick_name(get());
    }

    /**
        Returns the given stick's name.
        @param stick stick index.
        @return the given stick's name.
     */
    String getStickName(int stick) const {
        return al_get_joystick_stick_name(get(), stick);
    }

    /**
        Returns the given axis' name.
        @param stick stick index.
        @param axis axis index.
        @return the given stick axis' name.
     */
    String getAxisName(int stick, int axis) const {
        return al_get_joystick_axis_name(get(), stick, axis);
    }

    /**
        Returns the given button's name.
        @param button button index.
        @return the given button's name.
     */
    String getButtonName(int button) const {
        return al_get_joystick_button_name(get(), button);
    }

    /**
        Returns the given stick's flags.
        @param stick stick index.
        @return the given stick's flags.
     */
    int getStickFlags(int stick) const {
        return al_get_joystick_stick_flags(get(), stick);
    }

    /**
        Returns the joystick's number of sticks.
        @return the joystick's number of sticks.
     */
    int getNumSticks() const {
        return al_get_joystick_num_sticks(get());
    }

    /**
        Returns the joystick's number of axes.
        @param stick stick index.
        @return the joystick's number of axes.
     */
    int getNumAxes(int stick) const {
        return al_get_joystick_num_axes(get(), stick);
    }

    /**
        Returns the joystick's number of buttons.
        @return the joystick's number of buttons.
     */
    int getNumButtons() const {
        return al_get_joystick_num_buttons(get());
    }

    /**
        Returns the joystick event source.
        @return the joystick event source.
     */
    static EventSource getEventSource() {
        return EventSource(al_get_joystick_event_source(), false);
    }

    /**
        constructor from Allegro object.
        @param object allegro object.
        @param managed if true, the object will be deleted automatically when its last reference will be deleted.
     */
    Joystick(ALLEGRO_JOYSTICK *object, bool managed = true) : Shared(object, managed, al_release_joystick) {
    }
};


} //namespace alx


#endif //ALX_JOYSTICK_HPP
