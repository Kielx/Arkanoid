#include "Ball.h"
#include <SFML/Graphics.hpp>

Ball::Ball(float startX, float startY)
{
	sf::CircleShape shape;
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(startX, startY);
	this->shape = shape;

}

Ball::~Ball()
{
}
