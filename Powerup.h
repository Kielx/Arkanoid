/**
 * @file Powerup.h
 * @brief This file contains the Powerup class.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

 /**
  * @class Powerup
  * @brief This class represents a Powerup in the game.
  */
class Powerup
{
public:
    /**
     * @brief The radius of the coin.
     */
    float coinRadius{ 16.f };

    /**
     * @brief The position of the Powerup.
     */
    sf::Vector2f position;

    /**
     * @brief The velocity of the Powerup.
     */
    sf::Vector2f velocity = { 0.f, 2.f };

    /**
     * @brief The texture of the Powerup.
     */
    sf::Texture texture;

    /**
     * @brief Represents the shape of the Powerup.
     */
    sf::CircleShape shape;

    /**
     * @brief Clock to track time.
     */
    sf::Clock clock;

    /**
     * @brief The type of the Powerup.
     */
    int powerupType = 0;

    /**
     * @brief Represents whether the Powerup is destroyed or not.
     */
    bool destroyed{ false };

    /**
     * @brief Constructor for the Powerup class.
     * @param posX The x-coordinate of the Powerup.
     * @param posY The y-coordinate of the Powerup.
     * @param powerupType The type of the Powerup.
     * @param texture The texture of the Powerup.
     */
    Powerup(float posX, float posY, int powerupType, sf::Texture& texture);

    /**
     * @brief Updates the Powerup's state.
     */
    void update();

    /**
     * @brief Gets the x-coordinate of the Powerup.
     * @return The x-coordinate of the Powerup.
     */
    float x() { return shape.getPosition().x; }

    /**
     * @brief Gets the y-coordinate of the Powerup.
     * @return The y-coordinate of the Powerup.
     */
    float y() { return shape.getPosition().y; }

    /**
     * @brief Gets the left boundary of the Powerup.
     * @return The left boundary of the Powerup.
     */
    float left() { return x() - shape.getTextureRect().width / 2.f; }

    /**
     * @brief Gets the right boundary of the Powerup.
     * @return The right boundary of the Powerup.
     */
    float right() { return x() + shape.getTextureRect().width / 2.f; }

    /**
     * @brief Gets the top boundary of the Powerup.
     * @return The top boundary of the Powerup.
     */
    float top() { return y() - shape.getTextureRect().height / 2.f; }

    /**
     * @brief Gets the bottom boundary of the Powerup.
     * @return The bottom boundary of the Powerup.
     */
    float bottom() { return y() + shape.getTextureRect().height / 2.f; }
};
