#ifndef ALX_APPLICATION_HPP
#define ALX_APPLICATION_HPP


#include "Display.hpp"
#include "EventQueue.hpp"
#include "Timer.hpp"


namespace alx {


/**
    Helper class that takes care of the Allegro and add-ons initialization/cleanup, display/event queue creation etc.
 */
class Application {
public:
    /**
        Installs Allegro and the addons.
        Creates the display, event queue and one timer.
        @param displayWidth the display width; if 0, no display is created.
        @param displayHeight the displayHeight; if 0, no display id created.
        @param timerFPS frames per second for the timer; if 0, no timer is created.
        @param installKeyboard if true, install the keyboard module.
        @param installMouse if true, install the mouse module.
        @param installJoystick if true, it installs the joystick module.
        @param initAudio if true, it installs the audio addon.
        @param initAudioCodecs if true, it installs the audio codecs addon.
        @param initFonts if true, it installs the fonts addon.
        @param initTTF if true, it installs the truetype fonts addon.
        @param initImage if true, it installs the image addon.
        @param initPrimitives if true, it installs the primitives addon.
     */
    Application(
        int displayWidth = 1024,
        int displayHeight = 768,
        int timerFPS = 60,
        bool installKeyboard = true,
        bool installMouse = true,
        bool installJoystick = true,
        bool initAudio = true,
        bool initAudioCodecs = true,
        bool initFonts = true,
        bool initTTF = true,
        bool initImage = true,
        bool initPrimitives = true);

    /**
        Uninstalls all the installed resources and then uninstalls allegro.
     */
    ~Application();

    /**
        Returns the display.
        @return the display.
     */
    const Display &getDisplay() const {
        return m_display;
    }

    /**
        Returns the display.
        @return the display.
     */
    Display &getDisplay() {
        return m_display;
    }

    /**
        Returns the event queue.
        @return the event queue.
     */
    const EventQueue &getEventQueue() const {
        return m_eventQueue;
    }

    /**
        Returns the event queue.
        @return the event queue.
     */
    EventQueue &getEventQueue() {
        return m_eventQueue;
    }

    /**
        Returns the timer.
        @return the timer.
     */
    const Timer &getTimer() const {
        return m_timer;
    }

    /**
        Returns the timer.
        @return the timer.
     */
    Timer &getTimer() {
        return m_timer;
    }

    /**
        Executes an event loop.
        It does not return until the function 'exitEventLoop' is invoked.
     */
    void doEventLoop();

    /**
        Exits the current event loop.
     */
    void exitEventLoop();

private:
    Display m_display;
    EventQueue m_eventQueue;
    Timer m_timer;
};


} //namespace alx


#endif //ALX_APPLICATION_HPP
