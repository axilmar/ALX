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
#include "Voice.hpp"
#include "Font.hpp"
#include "NativeFileDialog.hpp"
#include "NativeTextLog.hpp"
#include "VertexDecl.hpp"
#include "Application.hpp"


using namespace std;
using namespace alx;


int main() {
    Application app1;

    UserEventSource ues;
    app1.getEventQueue() << ues;

    for(;;) {
        Event event = app1.getEventQueue().waitForEvent();
        switch (event.getType()) {
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.getKeyboardKeycode()) {
                    case ALLEGRO_KEY_ESCAPE:
                        goto END;
                }
                break;

            case ALLEGRO_EVENT_TIMER:
                if (event.getTimer() == app1.getTimer()) cout << "timer!\n";
                break;
        }
    }

    END:

	return 0;
}
