#include <SFML/Graphics.hpp>

#include "Brush.hpp"
#include "Eraser.hpp"
#include "ToolManager.hpp"
#include "ScrollBarButton.hpp"
#include "ColorButton.hpp"
#include "SizeButton.hpp"
#include "ColorButtonManager.hpp"
#include "SizeButtonManager.hpp"
#include "ToolButtonManager.hpp"
#include "CanvasWindow.hpp"
#include "PainterManager.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "";
const unsigned FRAME_RATE_LIMIT = 144;

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

    ToolManager toolManager(2);
    toolManager.addTool(new Brush());
    toolManager.addTool(new Eraser());

    const size_t nColorButtons = 3;
    ColorButton colorButtons[nColorButtons] = 
    {
        ColorButton(1700, 400, sf::Color::Red),
        ColorButton(1700, 500, sf::Color::Green),
        ColorButton(1700, 600, sf::Color::Blue)
    };

    ColorButtonManager colorButtonManager;
    for (size_t i = 0; i < nColorButtons; i++){
        colorButtonManager.addColorButton(colorButtons[i]);   
    }

    SizeButton sizeButton(1700, 700, 160, 90);
    SizeButtonManager sizeButtonManager(sizeButton);

    ToolButton brushButton(225, 175, "images/brush.png");
    brushButton.setTool(toolManager.tools_[0]);
    ToolButton eraserButton(225, 300, "images/eraser.png");
    eraserButton.setTool(toolManager.tools_[1]);

    ToolButtonManager toolButtonManager(2);
    toolButtonManager.addTool(&brushButton);
    toolButtonManager.addTool(&eraserButton);

    CanvasWindow canvasWindow(375, 175);

    PainterManager painterManager(toolManager, colorButtonManager, sizeButtonManager, toolButtonManager, canvasWindow);

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

            if (event.type == sf::Event::MouseButtonReleased) {
                painterManager.onMouseReleased((unsigned) mousePosition.x, (unsigned) mousePosition.y);
            }
		}

        painterManager.onMouseMove((unsigned) mousePosition.x, (unsigned) mousePosition.y);
        painterManager.draw(window);
        window.display();
		window.clear();
	}

    delete toolManager.tools_[0];
    delete toolManager.tools_[1];

	return 0;
}
