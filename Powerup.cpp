#include "Powerup.h"
#include <SFML/Graphics.hpp>


Powerup::Powerup(float posX, float posY, int powerupType, sf::Texture& texture)
{
	this->powerupType = powerupType;
	this->texture = texture;

	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setOrigin(16.f, 16.f);
	sprite.rotate(90);
	 if (powerupType == 1) {
		sprite.setColor(sf::Color::Red);
	}
	else if (powerupType == 2) {
		sprite.setColor(sf::Color::Yellow);
	}

}

void Powerup::update()
{
	sprite.move(velocity);
	sf::IntRect newTextureRect = sprite.getTextureRect();
	if (clock.getElapsedTime().asSeconds() > 0.2f) {
		clock.restart();
		newTextureRect.left += 32;
		if (newTextureRect.left >= 32 * 8)
			newTextureRect.left = 0;
		sprite.setTextureRect(newTextureRect);
	}
	
}