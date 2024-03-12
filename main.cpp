#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Arkanoid!");
    sf::CircleShape shape(300.f);
    shape.setFillColor(sf::Color::Green);
    shape.move(100, 100);

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
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
					shape.move(-10, 0);

				}
                if (event.key.code == sf::Keyboard::Right)
                {
					shape.move(10, 0);
				}
                if (event.key.code == sf::Keyboard::Up)
                {
					shape.move(0, -10);
				}
                if (event.key.code == sf::Keyboard::Down)
                {
					shape.move(0, 10);
				}
			}
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}