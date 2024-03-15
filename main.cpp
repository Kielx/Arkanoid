#include <SFML/Graphics.hpp>
#include "Ball.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    constexpr int windowWidth{ 800 }, windowHeight{ 600 };
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Ball ball(windowWidth / 2, windowHeight / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}

			
        }

        window.clear();
        window.draw(ball.shape);
        window.display();
    }

    return 0;
}