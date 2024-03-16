#pragma once
#include "Global.h" 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Ball
{
	public:
	sf::CircleShape shape;
	sf::Texture texture;
    sf::SoundBuffer wallHitBuffer;
    sf::Sound wallHit;
    sf::SoundBuffer brickHitBuffer;
    sf::Sound brickHit;
    sf::SoundBuffer paddleHitBuffer;
    sf::Sound paddleHit;


	// Let's create some constants for the Ball class.
	const float ballRadius{ 10.f }, ballVelocity{ 8.f };

	// 2D vector that stores the Ball's velocity.
	sf::Vector2f velocity{ -ballVelocity, -ballVelocity };

    Ball(float startX, float startY);
    ~Ball();

    void update();

    // We can also create "property" methods to easily
    // get commonly used values.
    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getRadius(); }
    float right() const { return x() + shape.getRadius(); }
    float top() const { return y() - shape.getRadius(); }
    float bottom() const { return y() + shape.getRadius(); }


};

