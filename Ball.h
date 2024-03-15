#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
	public:
	sf::CircleShape shape;
	sf::Texture texture;
	Ball(float startX, float startY);
	~Ball();
};

