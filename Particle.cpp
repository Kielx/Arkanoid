#include <SFML/Graphics.hpp>

class Particle {
public:

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Texture texture;
    sf::CircleShape shape;
    sf::Color color;
    bool right;
    float gravity = 0.05f; // Adjust as needed


    Particle(sf::Vector2f position, bool right, sf::Texture &texture) : position(position){
        
        shape.setPosition(position);
        shape.setRadius(13);
        shape.setPointCount(4);
        shape.setTexture(&texture);
        this->right = right;


        // Set an initial upward velocity
        velocity.y = -2.5f; // Adjust as needed
        // Set a random horizontal velocity
        velocity.x = (std::rand() % 20 - 10) / 40.0f; // Adjust as needed
    }

    void update(float dt) {
        // Apply gravity to the vertical velocity
        velocity.y += gravity * dt;
        // Apply velocity to position
        position += velocity * dt;
        // Update the shape's position
        shape.setPosition(position);
        right ? shape.rotate(2) : shape.rotate(-2);
        right ? shape.move(1, 0) : shape.move(-1, 0);
    }
   
};