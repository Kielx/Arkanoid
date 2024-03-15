#pragma once
#include "Global.h" 
#include <SFML/Graphics.hpp>
class Ball
{
	public:
	sf::CircleShape shape;
	sf::Texture texture;
	// Let's create some constants for the Ball class.
	const float ballRadius{ 10.f }, ballVelocity{ 8.f };

	// 2D vector that stores the Ball's velocity.
	sf::Vector2f velocity{ -ballVelocity, -ballVelocity };

    void update()
    {
        shape.move(velocity);

        // We need to keep the ball "inside the screen".

        // If it's leaving toward the left, we need to set
        // horizontal velocity to a positive value (towards the right).
        if (left() < 0) velocity.x = ballVelocity;

        // Otherwise, if it's leaving towards the right, we need to
        // set horizontal velocity to a negative value (towards the left).
        else if (right() > windowWidth)
            velocity.x = -ballVelocity;

        // The same idea can be applied for top/bottom collisions.
        if (top() < 0)
            velocity.y = ballVelocity;
        else if (bottom() > windowHeight)
            velocity.y = -ballVelocity;
    }

    // We can also create "property" methods to easily
// get commonly used values.
    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getRadius(); }
    float right() { return x() + shape.getRadius(); }
    float top() { return y() - shape.getRadius(); }
    float bottom() { return y() + shape.getRadius(); }

	Ball(float startX, float startY);
	~Ball();
};

