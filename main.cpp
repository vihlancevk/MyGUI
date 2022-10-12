#include <SFML/Graphics.hpp>

#include "ButtonManager.hpp"
#include "Button.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "";
const unsigned FRAME_RATE_LIMIT = 60;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

    ButtonManager buttonManager
    (
        3,
        Button (1525, 400, Color::RED),
        Button (1525, 500, Color::GREEN),
        Button (1525, 600, Color::BLUE)   
    );

	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                if (event.key.code == sf::Keyboard::W)
                    continue;

                if (event.key.code == sf::Keyboard::S)
                    continue;
			}

            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                }
            }
		}

        buttonManager.draw(window);

        window.display();
		window.clear();
	}

	return 0;
}
