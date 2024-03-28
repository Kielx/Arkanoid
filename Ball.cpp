#include "Ball.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

Ball::Ball(float startX, float startY, sf::Texture &texture)
{


	texture.setSmooth(true);
    shape.setRadius(10.f);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(startX, startY);
    shape.setTexture(&texture);


    if (!wallHitBuffer.loadFromFile("./sounds/wallHit.wav"))
    {
        // error...
    }
    wallHit.setBuffer(wallHitBuffer);
    wallHit.setVolume(50);

    if (!brickHitBuffer.loadFromFile("./sounds/brickHit.ogg"))
    {
		// error...
	}
    brickHit.setBuffer(brickHitBuffer);

    





	this->shape = shape;


}

Ball::~Ball()
{
}

void Ball::update()
{
    if (gameStopped) {
        velocity.x = 0;
        velocity.y = 0;
        Ball::shape.setPosition(windowWidth / 2, windowHeight - 75);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			gameStopped = false;
			velocity.x = -ballVelocity;
			velocity.y = -ballVelocity;
		}

        return;
    }
    shape.move(velocity);
    shape.rotate(5.f);

    // We need to keep the ball "inside the screen".

    // If it's leaving toward the left, we need to set
    // horizontal velocity to a positive value (towards the right).
    if (left() < 0) {
        velocity.x = ballVelocity;
        wallHit.play();
    }

    // Otherwise, if it's leaving towards the right, we need to
    // set horizontal velocity to a negative value (towards the left).
    else if (right() > windowWidth)
        {
        velocity.x = -ballVelocity;
        wallHit.play();
        }


    // The same idea can be applied for top/bottom collisions.
    if (top() < 0)
        velocity.y = ballVelocity;

}

void Ball::reset()
{
	shape.setPosition(windowWidth / 2, windowHeight - 75);
	velocity.x = -ballVelocity;
	velocity.y = -ballVelocity;
}