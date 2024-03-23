#include "LifeIndicator.h"

#include "Global.h"

#include <SFML/Graphics.hpp>

LifeIndicator::LifeIndicator(float posX, float posY, sf::Texture &texture)
{
	lifeIndicatorShape.setTexture(&texture);
	lifeIndicatorShape.setPosition(posX, posY);
	lifeIndicatorShape.setSize({ 50, 10 });
	lifeIndicatorShape.setOrigin(25.f, 25.f);


}