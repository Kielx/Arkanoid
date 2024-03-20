#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
	public:
	sf::RectangleShape shape;
	static const int countBlocksX, countBlocksY;
	static const float blockWidth, blockHeight;
	int hp;


	// This boolean value will be used to check
	// whether a brick has been hit or not.
	bool destroyed{ false };

	// The constructor is almost identical to the `Paddle` one.
	Brick(float mX, float mY, sf::Texture &texture, int hp);

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }

	void updateHp(int hp);

};

