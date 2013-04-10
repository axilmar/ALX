#include "Event.hpp"


namespace alx {


const EventType<Event> Event::JOYSTICK_AXIS("JoystickAxis");
const EventType<Event> Event::JOYSTICK_BUTTON_DOWN("JoystickButtonDown");
const EventType<Event> Event::JOYSTICK_BUTTON_UP("JoystickButtonUp");
const EventType<Event> Event::JOYSTICK_CONFIGURATION("JoystickConfiguration");
const EventType<Event> Event::KEY_DOWN("KeyDown");
const EventType<Event> Event::KEY_CHAR("KeyChar");
const EventType<Event> Event::KEY_UP("KeyUp");
const EventType<Event> Event::MOUSE_AXES("MouseAxes");
const EventType<Event> Event::MOUSE_BUTTON_DOWN("MouseButtonDown");
const EventType<Event> Event::MOUSE_BUTTON_UP("MouseButtonUp");
const EventType<Event> Event::MOUSE_ENTER_DISPLAY("EnterDisplay");
const EventType<Event> Event::MOUSE_LEAVE_DISPLAY("LeaveDisplay");
const EventType<Event> Event::MOUSE_WARPED("MouseWraped");
const EventType<Event> Event::TIMER("Timer");
const EventType<Event> Event::DISPLAY_EXPOSE("Expose");
const EventType<Event> Event::DISPLAY_RESIZE("Resize");
const EventType<Event> Event::DISPLAY_CLOSE("Close");
const EventType<Event> Event::DISPLAY_LOST("DisplayLost");
const EventType<Event> Event::DISPLAY_FOUND("DisplayFound");
const EventType<Event> Event::DISPLAY_SWITCH_IN("DisplaySwitchIn");
const EventType<Event> Event::DISPLAY_SWITCH_OUT("DisplaySwitchOut");
const EventType<Event> Event::DISPLAY_ORIENTATION("DisplayOrination");
const EventType<Event> Event::NATIVE_DIALOG_CLOSE("NativeDialogClose");



} //namespace alx
