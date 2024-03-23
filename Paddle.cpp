#include "Paddle.h"
#include "Global.h"
#include <SFML/Graphics.hpp>


Paddle::Paddle(float mX, float mY)
{
	if (!texture.loadFromFile("./images/paddleBlue.png"))
	{
		// error...
	}
	texture.setSmooth(true);
	shape.setTexture(&texture);
	shape.setPosition(mX, mY);
	shape.setSize({ paddleWidth, paddleHeight });
	//shape.setFillColor(sf::Color::Red);
	shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
}


void Paddle::update()
{
	shape.move(velocity);

	// To move the paddle, we check if the user is pressing
	// the left or right arrow key: if so, we change the velocity.

	// To keep the paddle "inside the window", we change the velocity
	// only if its position is inside the window.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && left() > 0)
		velocity.x = -paddleVelocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				right() < windowWidth)
		velocity.x = paddleVelocity;

	// If the user isn't pressing anything, stop moving.
	else
		velocity.x = 0;
}

void Paddle::reset()
{
	shape.setPosition(windowWidth / 2, windowHeight - 50);
	velocity.x = 0;
}