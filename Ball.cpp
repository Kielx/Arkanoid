#include "Ball.h"

#include <SFML/Graphics.hpp>



Ball::Ball(float startX, float startY)
{

	if (!texture.loadFromFile("./images/ball.png")) 
	{
		// error...
	}
	texture.setSmooth(true);

	shape.setRadius(10.f);
	shape.setPosition(startX, startY);
	shape.setTexture(&texture);

	this->shape = shape;


}

Ball::~Ball()
{
}
