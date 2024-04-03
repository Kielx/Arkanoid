/**
 * @file Brick.h
 * @brief This file contains the Brick class.
 */

#pragma once
#include <SFML/Graphics.hpp>

 /**
  * @class Brick
  * @brief This class represents a Brick in the game.
  */
class Brick
{
public:
    /**
     * @brief Represents the shape of the Brick.
     */
    sf::RectangleShape shape;

    /**
     * @brief The number of blocks in the x-direction.
     */
    static const int countBlocksX;

    /**
     * @brief The number of blocks in the y-direction.
     */
    static const int countBlocksY;

    /**
     * @brief The width of a block.
     */
    static const float blockWidth;

    /**
     * @brief The height of a block.
     */
    static const float blockHeight;

    /**
     * @brief The hit points of the Brick.
     */
    int hp;

    /**
     * @brief Represents whether the Brick is destroyed or not.
     */
    bool destroyed{ false };

    /**
     * @brief Constructor for the Brick class.
     * @param mX The x-coordinate of the Brick.
     * @param mY The y-coordinate of the Brick.
     * @param texture The texture of the Brick.
     * @param hp The hit points of the Brick.
     */
    Brick(float mX, float mY, sf::Texture& texture, int hp);

    /**
     * @brief Gets the x-coordinate of the Brick.
     * @return The x-coordinate of the Brick.
     */
    float x() { return shape.getPosition().x; }

    /**
     * @brief Gets the y-coordinate of the Brick.
     * @return The y-coordinate of the Brick.
     */
    float y() { return shape.getPosition().y; }

    /**
     * @brief Gets the left boundary of the Brick.
     * @return The left boundary of the Brick.
     */
    float left() { return x() - shape.getSize().x / 2.f; }

    /**
     * @brief Gets the right boundary of the Brick.
     * @return The right boundary of the Brick.
     */
    float right() { return x() + shape.getSize().x / 2.f; }

    /**
     * @brief Gets the top boundary of the Brick.
     * @return The top boundary of the Brick.
     */
    float top() { return y() - shape.getSize().y / 2.f; }

    /**
     * @brief Gets the bottom boundary of the Brick.
     * @return The bottom boundary of the Brick.
     */
    float bottom() { return y() + shape.getSize().y / 2.f; }

    /**
     * @brief Updates the hit points of the Brick.
     * @param hp The new hit points of the Brick.
     */
    void updateHp(int hp);
};
