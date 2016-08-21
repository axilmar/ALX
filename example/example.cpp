#include <vector>
#include "alx.hpp"
#include <allegro5/allegro_image.h>
using namespace alx;


//a sprite class
class Sprite {
public:
    //position
    Point<int> position;

    //velocity
    Point<int> velocity;

    //bitmap
    Bitmap bitmap;

    //Sprite
    Sprite(const Point<int> &pos, const Bitmap &bmp) : position(pos), bitmap(bmp) {
    }

    //draws the bitmap
    void draw() const {
        bitmap.draw(position.getX(), position.getY());
    }

    //get rect
    Rect<int> getRect() const {
        return Rect<int>(position, bitmap.getSize());
    }
};


typedef std::shared_ptr<Sprite> SpritePtr;


size_t rnd(size_t n) {
    return rand() % n;
}


//check collision between two sprites
bool collision(const Sprite &a, const Sprite &b) {
    return a.getRect().intersects(b.getRect());
}


//deflects the ball off a block
void deflectBall(Sprite &ball, const Sprite &block) {
    Rect<int> ballRect = ball.getRect();
    Rect<int> blockRect = block.getRect();

    if (ballRect.getLeft() == blockRect.getRight()) {
        ball.velocity.setX(1);
    }
    else if (ballRect.getRight() == blockRect.getLeft()) {
        ball.velocity.setX(-1);
    }

    if (ballRect.getTop() == blockRect.getBottom()) {
        ball.velocity.setY(1);
    }
    else if (ballRect.getBottom() == blockRect.getTop()) {
        ball.velocity.setY(-1);
    }
}


//main
int main() {
    //install allegro as needed
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    //resources
    Display display(640, 480);
    EventQueue eventQueue;
    Timer timer(1./60);
    UserEventSource ues;

    //bind the resources to the event queue
    eventQueue << Keyboard::getEventSource() << Mouse::getEventSource() << display << timer << ues;

    //bitmaps
    Bitmap paddleBmp("data/paddle.bmp");
    paddleBmp.convertMaskToAlpha(Color(0xFFFFFFFF));
    Bitmap ballBmp("data/ball.bmp");
    ballBmp.convertMaskToAlpha(Color(0xFFFFFFFF));
    std::vector<Bitmap> stones;
    for(int i = 1; i <= 23; ++i) {
        stones.push_back(Bitmap(String("data/stone") + i + ".jpg"));
    }

    //blocks
    std::vector<SpritePtr> blocks;
    int stoneWidth = stones[0].getWidth();
    int stoneHeight = stones[0].getHeight();
    int blockCols = display.getWidth() / stoneWidth;
    int blockRows = 2 * display.getHeight() / 3 / stoneHeight;
    for(int j = 0; j < blockRows; ++j) {
        for(int i = 0; i < blockCols; ++i) {
            blocks.push_back(SpritePtr(new Sprite(makePoint(i * stoneWidth, j * stoneHeight), stones[rnd(stones.size())])));
        }
    }

    //paddle and ball sprites
    auto paddleStartPos = makePoint(display.getWidth()/2 - paddleBmp.getWidth()/2, display.getHeight() - paddleBmp.getHeight());
    Sprite paddle(paddleStartPos, paddleBmp);
    auto ballStartPos = makePoint(paddle.position.getX() + paddleBmp.getWidth()/2 - ballBmp.getWidth()/2, paddle.position.getY() - ballBmp.getHeight());
    Sprite ball(ballStartPos, ballBmp);

    NativeTextLog textLog("ALX Example Debug Window");

    //the reset function
    auto reset = [&]() {
        paddle.position = paddleStartPos;
        ball.position = ballStartPos;
        ball.velocity.set(0, 0);
        MouseState mouseState;
        mouseState.retrieve();
        display.setMousePosition(display.getWidth()/2, mouseState.getMouseY());
    };


    //the update logic function
    auto updateLogic = [&]() {
        //update the ball position
        ball.position += ball.velocity;

        //invert the ball's horizontal velocity if it hits the screen horizontal end
        if (ball.position.getX() == 0 || ball.position.getX() == display.getWidth() - ball.bitmap.getWidth()) {
            ball.velocity.setX(-ball.velocity.getX());
        }

        //invert the ball's vertical velocity if it hits the screen top
        if (ball.position.getY() == 0) {
            ball.velocity.setY(1);
        }

        //reset the game if the ball reaches the bottom of the screen
        if (ball.position.getY() == display.getHeight()) {
            reset();
            return;
        }

        //check if the ball collides with a block
        for(auto &block : blocks) {
            if (block && collision(ball, *block)) {
                deflectBall(ball, *block);
                block.reset();
            }
        }

        //check if the ball collides with the paddle
        if (collision(ball, paddle)) {
            textLog << "collision between ball and paddle\n";
            if (ball.getRect().getCenterX() < paddle.getRect().getCenterX()) {
                ball.velocity.setX(-1);
            }
            else {
                ball.velocity.setX(1);
            }
            ball.velocity.setY(-1);
        }
    };

    //the function to use for drawing the current frame
    auto drawFrame = [&]() {
        //draw black background
        al_clear_to_color(Color(0));

        //draw the blocks
        for(auto &blockPtr : blocks) {
            if (blockPtr) blockPtr->draw();
        }

        //draw the paddle and ball
        paddle.draw();
        ball.draw();
    };

    //test fclose issue.
    {
        File test("text.txt", "r");
        test.close();
    }

    //test string issue
    {
        alx::FilePath path("bar/foo.txt");
        alx::String basename = path.getBasename();
        textLog << "basename = " << basename;
    }

    //event loop
    timer.start();
    bool loop = true;
    bool redraw = false;
    while (loop) {
        //time for redraw
        if (redraw && eventQueue.isEmpty()) {
            redraw = false;
            drawFrame();
            al_flip_display();
        }

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

            //mouse
            case ALLEGRO_EVENT_MOUSE_AXES:
                paddle.position.setX(std::max(0, std::min(event.getMouseX() - paddle.bitmap.getWidth()/2, display.getWidth() - paddle.bitmap.getWidth())));
                if (ball.velocity == Point<int>(0, 0)) {
                    ball.position.setX(paddle.position.getX() + paddle.bitmap.getWidth()/2 - ball.bitmap.getWidth()/2);
                }
                break;

            //button down
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (ball.velocity == Point<int>(0, 0)) {
                    ball.velocity.set(1, -1);
                }
                break;

            //timer
            case ALLEGRO_EVENT_TIMER:
                if (event.getTimer() == timer) {
                    redraw = true;
                    updateLogic();
                }
                break;

            //display close
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                loop = false;
                break;
        }
    }

	return 0;
}
