#include <SFML/Graphics.hpp>

#include "../plugin.h"
// #include "PluginEraser.hpp"
#include "PainterManager.hpp"
#include "CurvesFilterWindow.hpp"
#include "CanvasWindow.hpp"

sf::VertexArray& convertUnsignedIntArray2VertexArray(unsigned int* pixels, sf::VertexArray& vertexArrayPixels);

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "";
const unsigned FRAME_RATE_LIMIT = 144;

sf::VertexArray& convertUnsignedIntArray2VertexArray(unsigned int* pixels, sf::VertexArray& vertexArrayPixels) {
    for (unsigned int i = 0, j = 0; i < SCREEN_WEIGHT * SCREEN_HIGHT; i++, j += 4) {
        vertexArrayPixels[i].position = sf::Vector2f(static_cast<float>(i % SCREEN_WEIGHT),
                                                     static_cast<float>(i / SCREEN_WEIGHT));
        vertexArrayPixels[i].color = sf::Color((sf::Uint8) pixels[j],
                                               (sf::Uint8) pixels[j + 1],
                                               (sf::Uint8) pixels[j + 2],
                                               (sf::Uint8) pixels[j + 3]);
    }

    return vertexArrayPixels;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

    unsigned int* pixels = new unsigned int[SCREEN_WEIGHT * SCREEN_HIGHT * 4];
    for (unsigned i = 0; i < SCREEN_WEIGHT * SCREEN_HIGHT * 4 - (4 - 1); i += 4) {
        // r g b a
        pixels[i] = pixels[i + 1] = pixels[i + 2] = pixels[i + 3] = 255;
    }

    sf::VertexArray vertexArrayPixels(sf::Points, SCREEN_WEIGHT * SCREEN_HIGHT);

    size_t nPlugins = 1;
    PluginManager pluginManager(nPlugins);
    pluginManager.addPlugin(get_plugin());
    // TODO: class PlaginEraser {}
    // pluginManager.addPlugin(new PluginEraser (new Eraser(),
    //                                           new ToolPalette(275, 130, 400, 30),
    //                                           new ToolButton(100, 350, 135, 90, "images/eraser.png")));

    CurvesFilterWindow curvesFilterWindow(400, 400, 800, 450);

    CanvasWindow canvasWindow(275, 175, 1280, 720);

    PainterManager painterManager(pluginManager, curvesFilterWindow, canvasWindow);

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

                painterManager.on_key_press(event.key.code);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                painterManager.on_mouse_press(Pair<int>{mousePosition.x, mousePosition.y});
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                painterManager.on_mouse_release(Pair<int>{mousePosition.x, mousePosition.y});
            }
		}

        painterManager.on_mouse_move(Pair<int>{mousePosition.x, mousePosition.y});
        painterManager.draw(pixels, SCREEN_WEIGHT, SCREEN_HIGHT);
        window.draw(convertUnsignedIntArray2VertexArray(pixels, vertexArrayPixels));
        window.display();
		window.clear();
	}

    destroy_plugin();

    delete [] pixels;

	return 0;
}
