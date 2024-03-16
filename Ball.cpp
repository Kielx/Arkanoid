#include "Ball.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




Ball::Ball(float startX, float startY)
{

	if (!texture.loadFromFile("./images/ballBlue.png")) 
	{
		// error...
	}
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

    if (!paddleHitBuffer.loadFromFile("./sounds/paddleHit.flac"))
    {
		// error...
	}
	paddleHit.setBuffer(paddleHitBuffer);





	this->shape = shape;


}

Ball::~Ball()
{
}

void Ball::update()
{
    shape.move(velocity);

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
    else if (bottom() > windowHeight)
        velocity.y = -ballVelocity;
}
