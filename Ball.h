/**
 * @file Ball.h
 * @brief This file contains the Ball class.
 */

#pragma once
#include "Global.h" 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 /**
  * @class Ball
  * @brief This class represents a Ball in the game.
  */
class Ball
{
public:
    /**
     * @brief Represents the shape of the Ball.
     */
    sf::CircleShape shape;

    /**
     * @brief Represents the texture of the Ball.
     */
    sf::Texture texture;

    /**
     * @brief Sound buffer for the wall hit sound.
     */
    sf::SoundBuffer wallHitBuffer;

    /**
     * @brief Sound for when the Ball hits a wall.
     */
    sf::Sound wallHit;

    /**
     * @brief Sound buffer for the brick hit sound.
     */
    sf::SoundBuffer brickHitBuffer;

    /**
     * @brief Sound for when the Ball hits a brick.
     */
    sf::Sound brickHit;

    /**
     * @brief Radius of the Ball.
     */
    float ballRadius{ 10.f };

    /**
     * @brief Velocity of the Ball.
     */
    float ballVelocity{ 6.f };

    /**
     * @brief Represents whether the Ball is destroyed or not.
     */
    bool destroyed{ false };

    /**
     * @brief 2D vector that stores the Ball's velocity.
     */
    sf::Vector2f velocity{ -ballVelocity, -ballVelocity };

    /**
     * @brief Constructor for the Ball class.
     * @param startX The starting x-coordinate of the Ball.
     * @param startY The starting y-coordinate of the Ball.
     * @param texture The texture of the Ball.
     */
    Ball(float startX, float startY, sf::Texture& texture);

    /**
     * @brief Destructor for the Ball class.
     */
    ~Ball();

    /**
     * @brief Updates the Ball's state.
     */
    void update();

    /**
     * @brief Resets the Ball's state.
     */
    void reset();

    /**
     * @brief Gets the x-coordinate of the Ball.
     * @return The x-coordinate of the Ball.
     */
    float x() const { return shape.getPosition().x; }

    /**
     * @brief Gets the y-coordinate of the Ball.
     * @return The y-coordinate of the Ball.
     */
    float y() const { return shape.getPosition().y; }

    /**
     * @brief Gets the left boundary of the Ball.
     * @return The left boundary of the Ball.
     */
    float left() const { return x() - shape.getRadius(); }

    /**
     * @brief Gets the right boundary of the Ball.
     * @return The right boundary of the Ball.
     */
    float right() const { return x() + shape.getRadius(); }

    /**
     * @brief Gets the top boundary of the Ball.
     * @return The top boundary of the Ball.
     */
    float top() const { return y() - shape.getRadius(); }

    /**
     * @brief Gets the bottom boundary of the Ball.
     * @return The bottom boundary of the Ball.
     */
    float bottom() const { return y() + shape.getRadius(); }
};
