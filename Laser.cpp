#include "Laser.h"
#include "Global.h"
#include <SFML/Graphics.hpp>

Laser::Laser(float mX, float mY)
{
	shape.setSize({ laserWidth, laserHeight });
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(mX, mY);
	shape.setOrigin(laserWidth / 2.f, laserHeight / 2.f);
}

void Laser::update()
{
	shape.move(velocity);
}

void Laser::reset()
{
	shape.setPosition(windowWidth / 2, windowHeight - 50);
	shape.setSize({ laserWidth, laserHeight });
	velocity.x = 0;
}

