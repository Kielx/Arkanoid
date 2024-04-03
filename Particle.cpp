/**
 * @file Particle.cpp
 * @brief This file contains the Particle class.
 */

#include <SFML/Graphics.hpp>
#include "global.h"

 /**
  * @class Particle
  * @brief This class represents a Particle in the game.
  */
class Particle {
public:

    /**
     * @brief The position of the Particle.
     */
    sf::Vector2f position;

    /**
     * @brief The velocity of the Particle.
     */
    sf::Vector2f velocity;

    /**
     * @brief The texture of the Particle.
     */
    sf::Texture texture;

    /**
     * @brief Represents the shape of the Particle.
     */
    sf::CircleShape shape;

    /**
     * @brief The color of the Particle.
     */
    sf::Color color;

    /**
     * @brief Represents the direction of the Particle.
     */
    bool right;

    /**
     * @brief The gravity affecting the Particle.
     */
    float gravity = 0.05f;

    /**
     * @brief Constructor for the Particle class.
     * @param position The position of the Particle.
     * @param right The direction of the Particle.
     * @param texture The texture of the Particle.
     * @param hp The hit points of the Particle.
     */
    Particle(sf::Vector2f position, bool right, sf::Texture& texture, int hp) : position(position) {
        // Constructor implementation
    }

    /**
     * @brief Updates the Particle's state.
     * @param dt The time delta for the update.
     */
    void update(float dt) {
        // Update implementation
    }
};
