#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>
class LifeIndicator
{
	public:
	sf::RectangleShape lifeIndicatorShape;

	LifeIndicator(float posX, float posY, sf::Texture &texture);
};

