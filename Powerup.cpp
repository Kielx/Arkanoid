#include "Powerup.h"
#include <SFML/Graphics.hpp>


Powerup::Powerup(float posX, float posY, int powerupType, sf::Texture& texture)
{
	this->powerupType = powerupType;
	this->texture = texture;

	shape.setRadius(coinRadius);
	shape.setTexture(&texture);
	shape.setPosition(posX, posY);
	shape.setOrigin(coinRadius, coinRadius);

}

void Powerup::update()
{
	shape.move(velocity);
	if (clock.getElapsedTime().asSeconds() > 0.1f) {
		clock.restart();
		shape.rotate(30);
	}
	
}