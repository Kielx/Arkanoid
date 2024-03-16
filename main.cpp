#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Global.h" // for windowWidth and windowHeight
#include "Paddle.h"

int windowWidth{ 800 }, windowHeight{ 600 };
sf::SoundBuffer paddleHitBuffer;
sf::Sound paddleHit;


// Dealing with collisions: let's define a generic function
// to check if two shapes are intersecting (colliding).
template <class T1, class T2>
bool isIntersecting(T1& mA, T2& mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
        mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

// Let's define a function that deals with paddle/ball collision.
void testCollision(Paddle& mPaddle, Ball& mBall)
{
    // If there's no intersection, get out of the function.
    if (!isIntersecting(mPaddle, mBall)) return;



    // Otherwise let's "push" the ball upwards.
    mBall.velocity.y = -mBall.ballVelocity;

    // And let's direct it dependently on the position where the
    // paddle was hit.
    if (mBall.x() < mPaddle.x())
        mBall.velocity.x = -mBall.ballVelocity;
    else
        mBall.velocity.x = mBall.ballVelocity;

    if (!paddleHitBuffer.loadFromFile("./sounds/paddleHit.flac"))
    {
        // error...
    }
    paddleHit.setBuffer(paddleHitBuffer);
    paddleHit.setVolume(50);
    paddleHit.play();
}



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Ball ball(windowWidth / 2, windowHeight / 2);
    Paddle paddle(windowWidth / 2, windowHeight - 50 );


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}

			
        }

        window.clear();

        ball.update();
        paddle.update();

        // Let's test the collision every game loop iteration.
        testCollision(paddle, ball);

        window.draw(ball.shape);
        window.draw(paddle.shape);

        window.display();
    }

    return 0;
}