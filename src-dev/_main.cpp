#include <iostream>
#include "Config.hpp"
#include "Display.hpp"
#include "EventQueue.hpp"
#include "UserEventSource.hpp"


using namespace std;
using namespace alx;


int main() {
    al_init();
    al_install_keyboard();

    Display display(640, 480);
    UserEventSource userEventSource;

    EventQueue queue;
    queue << display << userEventSource << al_get_keyboard_event_source();

    for(;;) {
        Event event = queue.waitForEvent();
        switch (event.getEvent().type) {
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.getEvent().keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        goto END;
                    case ALLEGRO_KEY_SPACE:
                        userEventSource.emitUserEvent(new UserEvent(10000));
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
