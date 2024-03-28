#pragma once
#include <SFML/Graphics.hpp>
class Laser
{
	public:
	float laserWidth{ 2.f }, laserHeight{ 20.f }, laserVelocity{ 6.f };
	sf::RectangleShape shape;
	sf::Vector2f velocity { 0, -laserVelocity };

	Laser(float mX, float mY);

	bool destroyed{ false };
	void update();
	void reset();

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }
};

