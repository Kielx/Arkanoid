/**
 * @file LifeIndicator.h
 * @brief This file contains the LifeIndicator class.
 */

#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>

 /**
  * @class LifeIndicator
  * @brief This class represents a LifeIndicator in the game.
  */
class LifeIndicator
{
public:
    /**
     * @brief Represents the shape of the LifeIndicator.
     */
    sf::RectangleShape lifeIndicatorShape;

    /**
     * @brief Constructor for the LifeIndicator class.
     * @param posX The x-coordinate of the LifeIndicator.
     * @param posY The y-coordinate of the LifeIndicator.
     * @param texture The texture of the LifeIndicator.
     */
    LifeIndicator(float posX, float posY, sf::Texture& texture);
};
