#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Ball.h"
#include "Global.h" // for windowWidth and windowHeight
#include "Paddle.h"
#include "Brick.h"
#include "Particle.cpp"
#include <iostream>

int windowWidth{ 800 }, windowHeight{ 600 };
sf::SoundBuffer paddleHitBuffer;
sf::Sound paddleHit;
sf::SoundBuffer brickHitBuffer;
sf::Sound brickHit;
int score = 0;
sf::Text scoreText;


// Bricks broken particle vector
std::vector<Particle> particles;
sf::Texture particleTexture;


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
    srand((unsigned)time(NULL));
    // If there's no intersection, get out of the function.
    if (!isIntersecting(mPaddle, mBall)) return;



    // Otherwise let's "push" the ball upwards.
    mBall.velocity.y = -mBall.ballVelocity;

    // And let's direct it dependently on the position where the
    // paddle was hit.
    if (mBall.x() < mPaddle.x()) 
        mBall.velocity.x = -mBall.ballVelocity - (rand() % 2);
    else
        mBall.velocity.x = mBall.ballVelocity + (rand() % 2);

    if (!paddleHitBuffer.loadFromFile("./sounds/paddleHit.flac"))
    {
        // error...
    }
    paddleHit.setBuffer(paddleHitBuffer);
    paddleHit.setVolume(50);
    paddleHit.play();
}

// Here's the most complex part of our game: ball-brick collision.
void testCollision(Brick& mBrick, Ball& mBall)
{
    // If there's no intersection, get out of the function.
    if (!isIntersecting(mBrick, mBall)) return;

    // Otherwise, the brick has been hit!
    mBrick.destroyed = true;
    score += 100; // increase score

    // Let's calculate how much the ball intersects the brick
    // in every direction.
    float overlapLeft{ mBall.right() - mBrick.left() };
    float overlapRight{ mBrick.right() - mBall.left() };
    float overlapTop{ mBall.bottom() - mBrick.top() };
    float overlapBottom{ mBrick.bottom() - mBall.top() };

    // If the magnitude of the left overlap is smaller than the
    // right one we can safely assume the ball hit the brick
    // from the left.
    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));

    // We can apply the same idea for top/bottom collisions.
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    // Let's store the minimum overlaps for the X and Y axes.
    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    // If the magnitude of the X overlap is less than the magnitude
    // of the Y overlap, we can safely assume the ball hit the brick
    // horizontally - otherwise, the ball hit the brick vertically.

    // Then, upon our assumptions, we change either the X or Y velocity
    // of the ball, creating a "realistic" response for the collision.
    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -mBall.ballVelocity : mBall.ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -mBall.ballVelocity : mBall.ballVelocity;

    // Create particles

    if (!particleTexture.loadFromFile("./images/default_particle.png"))
    {
        // error...
    }

    particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), true, particleTexture));
	particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), false, particleTexture));
    particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), true, particleTexture));
    particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), false, particleTexture));

    if (!brickHitBuffer.loadFromFile("./sounds/brickHit.ogg"))
    {
        // error...
    }
    brickHit.setBuffer(brickHitBuffer);
    brickHit.setVolume(50);
    brickHit.play();
}



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("./fonts/kenvector_future.ttf")) {
        // handle error...
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(18); // choose appropriate size
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowWidth - 170, 8); // adjust position as needed


    Ball ball(windowWidth / 2, windowHeight / 2);
    Paddle paddle(windowWidth / 2, windowHeight - 50 );

    sf::Music music;
    if (!music.openFromFile("./sounds/backgroundMusic.ogg"))
        return -1; // error
    music.setPitch(0.75f);
    music.setLoop(true);
    music.setVolume(40.f);
    music.play();

    // We will use an `std::vector` to contain any number
    // of `Brick` instances.
    std::vector<Brick> bricks;




    // Load brick texture only once
    sf::Texture texture;
    if (!texture.loadFromFile("./images/default_block.png"))
    {
        // print the error to console
    }
    texture.setSmooth(true);


    // We fill up our vector via a 2D for loop, creating
    // bricks in a grid-like pattern.
    /*
    for (int iX{ 0 }; iX < Brick::countBlocksX; ++iX)
        for (int iY{ 0 }; iY < Brick::countBlocksY; ++iY)
            bricks.emplace_back(
                (iX + 1) * (Brick::blockWidth + 3) + 22, (iY + 2) * (Brick::blockHeight + 3), texture);
    */


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

        window.clear(sf::Color(30, 41, 59));

        if (bricks.empty()) {
            // We fill vector with random number of bricks
            int numberOfBricksX = rand() % 7 + 4;
            int numberOfBricksY = rand() % 3 + 2;
            int padLeft = 0;
            if (numberOfBricksX < 11) {
                 padLeft = (11 - numberOfBricksX) / 2;
            }
            for (int iX{ 0 }; iX < numberOfBricksX + padLeft; ++iX)
                for (int iY{ 0 }; iY < numberOfBricksY; ++iY) {
                    Brick newBrick = Brick((iX + 1) * (Brick::blockWidth + 3) + 22, (iY + 2) * (Brick::blockHeight + 3), texture);
                    if (iX < padLeft) {
						newBrick.destroyed = true;
					}
                    bricks.push_back(newBrick);
                }
                    

		}


        ball.update();
        paddle.update();

        // Let's test the collision every game loop iteration.
        testCollision(paddle, ball);

        // We use another C++11 foreach loop to test collisions
        // between the ball and EVERY brick.
        for (auto& brick : bricks) testCollision(brick, ball);

        // And we use the "erase-remove idiom" to remove all `destroyed`
        // blocks from the block vector - using a cool C++11 lambda!
        bricks.erase(remove_if(begin(bricks), end(bricks),
            [](const Brick& mBrick)
            {
                return mBrick.destroyed;
            }),
            end(bricks));

        window.draw(ball.shape);
        window.draw(paddle.shape);

        for (auto& brick : bricks) window.draw(brick.shape);

        // Update particles
        for (Particle& p : particles) {
            p.update(2);
        }

		// Draw particles
        for (const Particle& p : particles) {
			window.draw(p.shape);
		}

        // Remove particles that are out of bounds
        particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) {
			return p.shape.getPosition().y > windowHeight;
			}), particles.end());

        // Update score
        scoreText.setString("Score: " + std::to_string(score));
		window.draw(scoreText);

        window.display();
    }

    return 0;
}