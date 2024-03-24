#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Powerup
{
	public:
	sf::Vector2f position;
	sf::Vector2f velocity = { 0.f, 2.f };
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect textureRect = { 0, 0, 32, 32 };
	sf::Clock clock;
	int powerupType = 0;


	Powerup(float posX, float posY, int powerupType, sf::Texture &texture);
	void update();

	float x() { return sprite.getPosition().x; }
	float y() { return sprite.getPosition().y; }
	float left() { return x() - sprite.getTextureRect().width / 2.f; }
	float right() { return x() + sprite.getTextureRect().width / 2.f; }
	float top() { return y() - sprite.getTextureRect().height / 2.f; }
	float bottom() { return y() + sprite.getTextureRect().height / 2.f;}
};

