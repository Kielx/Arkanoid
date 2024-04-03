/**
 * @file Laser.h
 * @brief This file contains the Laser class.
 */

#pragma once
#include <SFML/Graphics.hpp>

 /**
  * @class Laser
  * @brief This class represents a Laser in the game.
  */
class Laser
{
public:
    /**
     * @brief The width of the Laser.
     */
    float laserWidth{ 2.f };

    /**
     * @brief The height of the Laser.
     */
    float laserHeight{ 20.f };

    /**
     * @brief The velocity of the Laser.
     */
    float laserVelocity{ 6.f };

    /**
     * @brief Represents the shape of the Laser.
     */
    sf::RectangleShape shape;

    /**
     * @brief 2D vector that stores the Laser's velocity.
     */
    sf::Vector2f velocity{ 0, -laserVelocity };

    /**
     * @brief Constructor for the Laser class.
     * @param mX The x-coordinate of the Laser.
     * @param mY The y-coordinate of the Laser.
     */
    Laser(float mX, float mY);

    /**
     * @brief Represents whether the Laser is destroyed or not.
     */
    bool destroyed{ false };

    /**
     * @brief Updates the Laser's state.
     */
    void update();

    /**
     * @brief Resets the Laser's state.
     */
    void reset();

    /**
     * @brief Gets the x-coordinate of the Laser.
     * @return The x-coordinate of the Laser.
     */
    float x() { return shape.getPosition().x; }

    /**
     * @brief Gets the y-coordinate of the Laser.
     * @return The y-coordinate of the Laser.
     */
    float y() { return shape.getPosition().y; }

    /**
     * @brief Gets the left boundary of the Laser.
     * @return The left boundary of the Laser.
     */
    float left() { return x() - shape.getSize().x / 2.f; }

    /**
     * @brief Gets the right boundary of the Laser.
     * @return The right boundary of the Laser.
     */
    float right() { return x() + shape.getSize().x / 2.f; }

    /**
     * @brief Gets the top boundary of the Laser.
     * @return The top boundary of the Laser.
     */
    float top() { return y() - shape.getSize().y / 2.f; }

    /**
     * @brief Gets the bottom boundary of the Laser.
     * @return The bottom boundary of the Laser.
     */
    float bottom() { return y() + shape.getSize().y / 2.f; }
};
