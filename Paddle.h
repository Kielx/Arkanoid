/**
 * @file Paddle.h
 * @brief This file contains the Paddle class.
 */

#pragma once
#include <SFML/Graphics.hpp>

 /**
  * @class Paddle
  * @brief This class represents a Paddle in the game.
  */
class Paddle
{
public:
    /**
     * @brief The width of the Paddle.
     */
    const float paddleWidth{ 80.f };

    /**
     * @brief The height of the Paddle.
     */
    const float paddleHeight{ 20.f };

    /**
     * @brief The velocity of the Paddle.
     */
    const float paddleVelocity{ 7.f };

    /**
     * @brief Represents the shape of the Paddle.
     */
    sf::RectangleShape shape;

    /**
     * @brief Represents the texture of the Paddle.
     */
    sf::Texture texture;

    /**
     * @brief 2D vector that stores the Paddle's velocity.
     */
    sf::Vector2f velocity;

    /**
     * @brief Constructor for the Paddle class.
     * @param mX The x-coordinate of the Paddle.
     * @param mY The y-coordinate of the Paddle.
     */
    Paddle(float mX, float mY);

    /**
     * @brief Updates the Paddle's state.
     */
    void update();

    /**
     * @brief Resets the Paddle's state.
     */
    void reset();

    /**
     * @brief Gets the x-coordinate of the Paddle.
     * @return The x-coordinate of the Paddle.
     */
    float x() { return shape.getPosition().x; }

    /**
     * @brief Gets the y-coordinate of the Paddle.
     * @return The y-coordinate of the Paddle.
     */
    float y() { return shape.getPosition().y; }

    /**
     * @brief Gets the left boundary of the Paddle.
     * @return The left boundary of the Paddle.
     */
    float left() { return x() - shape.getSize().x / 2.f; }

    /**
     * @brief Gets the right boundary of the Paddle.
     * @return The right boundary of the Paddle.
     */
    float right() { return x() + shape.getSize().x / 2.f; }

    /**
     * @brief Gets the top boundary of the Paddle.
     * @return The top boundary of the Paddle.
     */
    float top() { return y() - shape.getSize().y / 2.f; }

    /**
     * @brief Gets the bottom boundary of the Paddle.
     * @return The bottom boundary of the Paddle.
     */
    float bottom() { return y() + shape.getSize().y / 2.f; }
};
