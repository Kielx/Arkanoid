#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Powerup
{
	public:
	float coinRadius{ 16.f };
	sf::Vector2f position;
	sf::Vector2f velocity = { 0.f, 2.f };
	sf::Texture texture;
	sf::CircleShape shape;
	sf::Clock clock;
	int powerupType = 0;

	// This boolean value will be used to check
	// whether powerup has been hit or not.
	bool destroyed{ false };


	Powerup(float posX, float posY, int powerupType, sf::Texture &texture);
	void update();

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getTextureRect().width / 2.f; }
	float right() { return x() + shape.getTextureRect().width / 2.f; }
	float top() { return y() - shape.getTextureRect().height / 2.f; }
	float bottom() { return y() + shape.getTextureRect().height / 2.f;}


};

