#include "Event.hpp"


namespace alx {


//check if the type represents an Allegro event or a user type event.
bool Event::_isUserEvent(int type) {
    switch (type) {
        case ALLEGRO_EVENT_JOYSTICK_AXIS:
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
        case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_KEY_CHAR:
        case ALLEGRO_EVENT_KEY_UP:
        case ALLEGRO_EVENT_MOUSE_AXES:
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
        case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
        case ALLEGRO_EVENT_MOUSE_WARPED:
        case ALLEGRO_EVENT_TIMER:
        case ALLEGRO_EVENT_DISPLAY_EXPOSE:
        case ALLEGRO_EVENT_DISPLAY_RESIZE:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        case ALLEGRO_EVENT_DISPLAY_LOST:
        case ALLEGRO_EVENT_DISPLAY_FOUND:
        case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
        case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
        case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
            return false;
    }
    return true;
}       


} //namespace alx
