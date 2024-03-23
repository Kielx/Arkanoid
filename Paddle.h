#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
	// Let's create some constants for the paddle.
	const float paddleWidth{ 80.f }, paddleHeight{ 20.f }, paddleVelocity{ 7.f };

    public:
	sf::RectangleShape shape;
    sf::Texture texture;
	sf::Vector2f velocity;

    // As with the ball, we construct the paddle with
    // arguments for initial position and pass the values
    // to the SFML `shape`.
    Paddle(float mX, float mY);    

    void update();
    void reset();

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getSize().x / 2.f; }
    float right() { return x() + shape.getSize().x / 2.f; }
    float top() { return y() - shape.getSize().y / 2.f; }
    float bottom() { return y() + shape.getSize().y / 2.f; }
};

