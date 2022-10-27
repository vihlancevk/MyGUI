#include <SFML/Graphics.hpp>

#include "Button.hpp"
#include "ButtonManager.hpp"
#include "CanvasWindow.hpp"
#include "PainterManager.hpp"
#include "Brush.hpp"
#include "Eraser.hpp"
#include "ToolManager.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "";
const unsigned FRAME_RATE_LIMIT = 144;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

    ToolManager toolManager;
    toolManager.addTool(new Brush(225, 175, "images/brush.png"));
    toolManager.addTool(new Eraser(225, 300, "images/eraser.png"));

    const size_t nButtons = 3;
    Button buttons[nButtons] = 
    {
        Button(1700, 400, Color::RED),
        Button(1700, 500, Color::GREEN),
        Button(1700, 600, Color::BLUE)
    };

    ButtonManager buttonManager(3);
    for (size_t i = 0; i < nButtons; i++){
        buttonManager.addButton(buttons[i]);   
    }

    CanvasWindow canvasWindow(375, 175);

    PainterManager painterManager(buttonManager, canvasWindow);

	sf::Event event;

	while (window.isOpen()) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

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
                painterManager.onMouseClick((unsigned) mousePosition.x, (unsigned) mousePosition.y);
            }
		}


        painterManager.onMouseMove((unsigned) mousePosition.x, (unsigned) mousePosition.y);
        painterManager.draw(window);
        toolManager.draw(window);
        window.display();
		window.clear();
	}

	return 0;
}
