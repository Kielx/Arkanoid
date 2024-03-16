#include "Brick.h"
#include <SFML/Graphics.hpp>

const int Brick::countBlocksX{ 11 }, Brick::countBlocksY{ 4 };
const float Brick::blockWidth{ 60.f }, Brick::blockHeight{ 20.f };

Brick::Brick(float mX, float mY, sf::Texture &texture) {

    shape.setPosition(mX, mY);
    shape.setSize({ blockWidth, blockHeight });
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	shape.setTexture(&texture);
}