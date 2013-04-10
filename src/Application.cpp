#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Application.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"


namespace alx {


//initializes Allegro
Application::Application(
    int displayWidth/* = 1024*/,
    int displayHeight/* = 768*/,
    int timerFPS/* = 60*/,
    bool installKeyboard /*= true*/,
    bool installMouse /*= true*/,
    bool installJoystick /*= true*/,
    bool initAudio /*= true*/,
    bool initAudioCodecs /*= true*/,
    bool initFonts /*= true*/,
    bool initTTF /*= true*/,
    bool initImage /*= true*/,
    bool initPrimitives /*= true*/)
:
    m_eventQueue(false)
{
    //install allegro
    al_init();
    if (installKeyboard) al_install_keyboard();
    if (installMouse) al_install_mouse();
    if (installJoystick) al_install_joystick();
    if (initAudio) al_install_audio();
    if (initAudioCodecs) al_init_acodec_addon();
    if (initFonts) al_init_font_addon();
    if (initTTF) al_init_ttf_addon();
    if (initImage) al_init_image_addon();
    if (initPrimitives) al_init_primitives_addon();

    //create the display
    if (displayWidth > 0 && displayHeight > 0) m_display = Display(displayWidth, displayHeight);

    //create the event queue
    m_eventQueue = EventQueue();

    //create the timer
    if (timerFPS > 0) m_timer = Timer(1.0 / timerFPS);

    //register the event sources
    if (installKeyboard) m_eventQueue << Keyboard::getEventSource();
    if (installMouse) m_eventQueue << Mouse::getEventSource();
    if (m_display) m_eventQueue << m_display;
    if (m_timer) m_eventQueue << m_timer;
}


//Uninstalls all the installed resources and then uninstalls allegro.
Application::~Application() {
    //reset resources before uninstalling
    m_timer.reset();
    m_eventQueue.reset();
    m_display.reset();

    //shutdown addons/uninstall modules and allegro
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_uninstall_audio();
    al_uninstall_joystick();
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_uninstall_system();
}


//Executes an event loop.
void Application::doEventLoop() {
    //TODO
}


//Exits the current event loop.
void Application::exitEventLoop() {
    //TODO
}


} //namespace alx
