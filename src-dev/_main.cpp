#include <iostream>
#include "Config.hpp"
#include "Display.hpp"
#include "EventQueue.hpp"
#include "UserEventSource.hpp"
#include "FileEntry.hpp"
#include "Fixed.hpp"
#include "Color.hpp"
#include "JoystickState.hpp"
#include "KeyboardState.hpp"
#include "State.hpp"


using namespace std;
using namespace alx;


class MyEvent : public UserEvent {
public:
    MyEvent() : UserEvent(10000) {
    }

    virtual ~MyEvent() {
        cout << "~MyEvent()\n";
    }
};


int main() {
    al_init();
    al_install_keyboard();

    Display display(640, 480);
    UserEventSource userEventSource;

    EventQueue queue;
    queue << display << userEventSource << al_get_keyboard_event_source();

    /*
    FileEntry dir(".");
    for(FileEntry entry : dir) {
        cout << entry.getPath() << endl;
    }
    */

    /*
    Fixed f1 = 14.5, f2 = 3;
    cout << (double)(f1 % f2);
    */

    //Color c = {0.1f, 0.2f, 0.3f, 0.4f};

    /*
    Joystick joy0(0);
    JoystickState state;
    state.readState(joy0);
    */

    //FilePath path(".");

    //State state;

    for(;;) {
        Event event = queue.waitForEvent();
        switch (event.getEvent().type) {
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.getEvent().keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        goto END;
                    case ALLEGRO_KEY_SPACE:
                        userEventSource.emitUserEvent(new MyEvent());
                        break;
                }
                break;

            case 10000:
                cout << "user event\n";
                break;
        }
    }

    END:

	return 0;
}
