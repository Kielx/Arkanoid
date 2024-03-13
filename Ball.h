#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
	public:
	sf::CircleShape shape;
	Ball(float startX, float startY);
	~Ball();
};

