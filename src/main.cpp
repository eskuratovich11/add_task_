#include "SFML/Graphics.hpp"
using namespace sf;
const float G = 10.0f;
enum FallingState{
    FALL,UP,NONE
};
struct Ball{
    CircleShape shape;
    FallingState fallingState;
    float time = 0,x_pos,y0,v0,stop;
    explicit Ball(float x_pos,float stop,const Color&color) : shape(CircleShape(32)),x_pos(x_pos),fallingState(FALL),y0(400),v0(0),stop(stop){
        shape.setFillColor(color);
    }
    void nextFrame(){
        time += .7f;
    }
};
Ball& calculate(Ball&ball){
    float y_pos;
    switch (ball.fallingState) {
        case FALL:
            y_pos = ball.y0 - G*ball.time*ball.time/2.0f;
            if(y_pos<=0){
                y_pos = 0;
                ball.time = 0;
                ball.v0 = sqrt(2.0f*G*ball.y0)*ball.stop;
                ball.fallingState = UP;
                break;
            }
            ball.nextFrame();
            break;
        case UP:
            if(ball.v0 - G*ball.time<=0){
                y_pos = ball.v0*ball.v0/(G*2);
                ball.y0 = y_pos;
                ball.time = 0;
                if(y_pos >= 0.1f) {
                    ball.fallingState = FALL;
                }else{
                    ball.fallingState = NONE;
                }
                break;
            }
            y_pos = ball.v0*ball.time - G*ball.time*ball.time/2.0f;
            ball.nextFrame();
            break;
        case NONE:
            y_pos = 0;
            break;
    }
    ball.shape.setPosition(ball.x_pos,400-y_pos);
    return ball;
}
int main()
{
    RenderWindow window(VideoMode(512, 512), "Auto");
    window.setFramerateLimit(30);
    Ball ball_state_1(0,.9f, Color::White),ball_state_2(256-32,.8f,Color::Blue),ball_state_3(512-64,.7f,Color::Red);
    Event event{};
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(calculate(ball_state_1).shape);
        window.draw(calculate(ball_state_2).shape);
        window.draw(calculate(ball_state_3).shape);
        window.display();
    }

    return 0;
}