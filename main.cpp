#include <SFML/Graphics.hpp>

#include "Brush.hpp"
#include "Eraser.hpp"
#include "ToolPalette.hpp"
#include "ToolManager.hpp"
#include "ScrollBarButton.hpp"
#include "ColorButton.hpp"
#include "SizeButton.hpp"
#include "ColorButtonManager.hpp"
#include "SizeButtonManager.hpp"
#include "ToolButtonManager.hpp"
#include "CurvesFilterWindow.hpp"
#include "CanvasWindow.hpp"
#include "PainterManager.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "";
const unsigned FRAME_RATE_LIMIT = 144;

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

    sf::VertexArray pixels(sf::Points, SCREEN_WEIGHT * SCREEN_HIGHT);
    for(unsigned i = 0; i < SCREEN_WEIGHT * SCREEN_HIGHT; i++) {
        pixels[i].position = sf::Vector2f(static_cast<float>(i % SCREEN_WEIGHT),
                                          static_cast<float>(i / SCREEN_WEIGHT));
        pixels[i].color = sf::Color::White;
    }

    ToolPalette toolPalette(275, 130, 400, 30);

    ToolManager toolManager(2, toolPalette);
    toolManager.addTool(new Brush());
    toolManager.addTool(new Eraser());

    const size_t nColorButtons = 3;
    ColorButton colorButtons[nColorButtons] = 
    {
        ColorButton(1600, 175, 160, 90, sf::Color::Red),
        ColorButton(1600, 275, 160, 90, sf::Color::Green),
        ColorButton(1600, 375, 160, 90, sf::Color::Blue)
    };

    ColorButtonManager colorButtonManager;
    for (size_t i = 0; i < nColorButtons; i++){
        colorButtonManager.addColorButton(colorButtons[i]);   
    }

    SizeButton sizeButton(1600, 805, 160, 90);
    SizeButtonManager sizeButtonManager(sizeButton);

    ToolButton brushButton(100, 225, 135, 90, "images/brush.png");
    brushButton.setTool(toolManager.tools_[0]);
    ToolButton eraserButton(100, 350, 135, 90, "images/eraser.png");
    eraserButton.setTool(toolManager.tools_[1]);

    ToolButtonManager toolButtonManager(2);
    toolButtonManager.addTool(&brushButton);
    toolButtonManager.addTool(&eraserButton);

    CurvesFilterWindow curvesFilterWindow(400, 400, 800, 450);

    CanvasWindow canvasWindow(275, 175, 1280, 720);

    PainterManager painterManager(toolManager, colorButtonManager, sizeButtonManager,
                                  toolButtonManager, curvesFilterWindow, canvasWindow);

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

                painterManager.onKeyboard(event.key.code);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                painterManager.onMouseClick((unsigned) mousePosition.x, (unsigned) mousePosition.y);
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                painterManager.onMouseReleased((unsigned) mousePosition.x, (unsigned) mousePosition.y);
            }
		}

        painterManager.onMouseMove((unsigned) mousePosition.x, (unsigned) mousePosition.y);
        window.draw(pixels);
        painterManager.draw(window);
        window.display();
		window.clear();
	}

    delete toolManager.tools_[0];
    delete toolManager.tools_[1];

	return 0;
}
