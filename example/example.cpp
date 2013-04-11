#include <vector>
#include "alx.hpp"
using namespace alx;


//a sprite class
class Sprite {
public:
    //position
    Point<float> position;

    //bitmap
    Bitmap bitmap;

    //Sprite
    Sprite(const Point<float> &pos, const Bitmap &bmp) : position(pos), bitmap(bmp) {
    }
};


//main
int main() {
    //install allegro as needed
    al_init();
    al_install_keyboard();
    al_install_mouse();

    //resources
    Display display(640, 480);
    EventQueue eventQueue;
    Timer timer(1./60);
    UserEventSource ues;

    //bind the resources to the event queue
    eventQueue << Keyboard::getEventSource() << Mouse::getEventSource() << display << timer << ues;

    //bitmaps
    Bitmap paddle("data/paddle.jpg");
    Bitmap ball("data/ball.jpg");
    std::vector<Bitmap> stones;
    for(int i = 1; i <= 23; ++i) {
        stones.push_back(Bitmap(String("stone") + i + ".jpg"));
    } 

    //the function to use for drawing the current frame
    auto drawFrame = []() {
        al_clear_to_color(Color(0));
    };

    //event loop
    timer.start();
    bool loop = true;
    bool redraw = false;
    while (loop) {
        //wait for event
        Event event = eventQueue.waitForEvent();

        //process event
        switch (event.getType()) {

            //key down
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.getKeyboardKeycode()) {

                    //end the loop
                    case ALLEGRO_KEY_ESCAPE:
                        loop = false;
                        break;
                }
                break;

            //timer
            case ALLEGRO_EVENT_TIMER:
                if (event.getTimer() == timer) redraw = true;
                break;
        }

        //time for redraw
        if (redraw && eventQueue.isEmpty()) {
            redraw = false;
            drawFrame();
            al_flip_display();
        }
    }

	return 0;
}
