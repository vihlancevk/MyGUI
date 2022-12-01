#include <dlfcn.h>
#include <SFML/Graphics.hpp>

#include "plugin.h"
#include "PainterManager.hpp"
#include "CurvesFilterWindow.hpp"
#include "CanvasWindow.hpp"

struct plugin {
    void* handle;
    IPlugin* (*get_plugin)();
    void (*destroy_plugin)();
};

void load_plugins();
void del_plugin();
void clear_pixels(unsigned int* pixels);
sf::VertexArray& convertUnsignedIntArray2VertexArray(unsigned int* pixels, sf::VertexArray& vertexArrayPixels);

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "";
const unsigned FRAME_RATE_LIMIT = 144;

const int nPlugins = 2;
const char* lib_names[nPlugins] = {"/home/kostya/C++-Ded/MyGUI/libPluginBrush.so",
                                    "/home/kostya/C++-Ded/MyGUI/libPluginEraser.so"}; 
plugin plugins[nPlugins] = {};

void load_plugins() {
    for (int i = 0; i < nPlugins; i++) {
        plugins[i].handle = dlopen(lib_names[i], RTLD_LAZY);
        if (!plugins[i].handle) {
            std::cout << dlerror();
            continue;
        }
        plugins[i].get_plugin = (IPlugin* (*)()) dlsym(plugins[i].handle, "get_plugin");
        plugins[i].destroy_plugin = (void (*)()) dlsym(plugins[i].handle, "destroy_plugin");
    }
}

void del_plugin() {
    for (int i = 0; i < nPlugins; i++) {
        if (!plugins[i].handle) {
            std::cout << dlerror();

            continue;
        }
        dlclose(plugins[i].handle);
    }
}

void clear_pixels(unsigned int* pixels) {
    for (unsigned i = 0; i < SCREEN_WEIGHT * SCREEN_HIGHT * 4 - (4 - 1); i += 4) {
        // r g b a
        pixels[i] = pixels[i + 1] = pixels[i + 2] = pixels[i + 3] = 255;
    }
}

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
    load_plugins();

	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

    unsigned int* pixels = new unsigned int[SCREEN_WEIGHT * SCREEN_HIGHT * 4];
    clear_pixels(pixels);

    sf::VertexArray vertexArrayPixels(sf::Points, SCREEN_WEIGHT * SCREEN_HIGHT);

    PluginManager pluginManager(nPlugins);
    pluginManager.addPlugin(plugins[0].get_plugin());
    pluginManager.addPlugin(plugins[1].get_plugin());

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
        clear_pixels(pixels);
        painterManager.draw(pixels, SCREEN_WEIGHT, SCREEN_HIGHT);
        window.draw(convertUnsignedIntArray2VertexArray(pixels, vertexArrayPixels));
        window.display();
		window.clear();
	}

    plugins[0].destroy_plugin();
    plugins[1].destroy_plugin();

    void del_plugin();

    delete [] pixels;

	return 0;
}
