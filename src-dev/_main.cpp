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
#include "System.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Keyboard.hpp"
#include "Transform.hpp"


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
    al_install_mouse();

    Display display(640, 480);
    UserEventSource userEventSource;

    EventQueue queue;

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

    //System::getStandardPath(ALLEGRO_USER_HOME_PATH);

    /*
    Mutex mtx;
    int x = mtx << [](){cout << "yo!"; return 1; };
    */

    //Condition c;

    Timer timer(1);

    queue << display << userEventSource << Keyboard::getEventSource() << timer;

    //timer.start();

    //Transform tr(true);

    String str = "the quick brown fox";
    str = {'a', 'b', 'c'};
    str.front() = 'f';
    for(char ch : str) {
        cout << ch;
    }
    cout << endl;

    for(;;) {
        Event event = queue.waitForEvent();
        switch (event.getType()) {
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.getKeyboardKeycode()) {
                    case ALLEGRO_KEY_ESCAPE:
                        goto END;
                    case ALLEGRO_KEY_SPACE:
                        userEventSource.emitUserEvent(new MyEvent());
                        break;
                }
                break;

            case ALLEGRO_EVENT_TIMER:
                if (event.getTimer() == timer) cout << "timer!\n";
                break;

            case 10000:
                cout << "user event\n";
                break;
        }
    }

    END:

	return 0;
}
