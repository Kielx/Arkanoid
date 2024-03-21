#include "Brick.h"
#include <SFML/Graphics.hpp>

const int Brick::countBlocksX{ 11 }, Brick::countBlocksY{ 4 };
const float Brick::blockWidth{ 60.f }, Brick::blockHeight{ 20.f };

Brick::Brick(float mX, float mY, sf::Texture &texture, int hp) {

	this->hp = hp;
    shape.setPosition(mX, mY);
    shape.setSize({ blockWidth, blockHeight });
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	shape.setTexture(&texture);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(1.f);

}

void Brick::updateHp(int hp) {
	this->hp = hp;
	if (hp == 1) {
		shape.setFillColor(sf::Color::White);
	}
	else if (hp == 2) {
		shape.setFillColor(sf::Color::Color(96,165,250));
	}
	else if (hp == 3) {
		shape.setFillColor(sf::Color::Yellow);
	}
	else if (hp == 4) {
		shape.setFillColor(sf::Color::Red);
	}
}