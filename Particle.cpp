#include <SFML/Graphics.hpp>

class Particle {
public:

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Texture texture;
    sf::CircleShape shape;
    sf::Color color;
    bool right;

    Particle(sf::Vector2f position, bool right) : position(position){
		shape.setFillColor(sf::Color::White);
        shape.setPosition(position);
        shape.setRadius(5);
        shape.setPointCount(3);
        shape.setOrigin(50, 50);
        this->right = right;
    }

    void update(float dt) {
        if (right) {
			shape.move(5, 5);
		}
        else {
			shape.move(-5, 5);
		}

    }
   
};