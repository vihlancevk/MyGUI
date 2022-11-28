#include "plugin.h"
#include "Eraser.hpp"
#include "ColorButton.hpp"
#include "ColorButtonManager.hpp"
#include "SizeButton.hpp"
#include "SizeButtonManager.hpp"
#include "EraserPalette.hpp"
#include "PropsEraser.hpp"
#include "EraserButton.hpp"

static IPlugin* pluginEraser = nullptr;

namespace eraser {
    IPlugin* get_plugin() {
        const size_t nColorButtons = 3;
        static ColorButton colorButtons[nColorButtons] = 
        {
            ColorButton(1600, 175, 160, 90, sf::Color::Red),
            ColorButton(1600, 275, 160, 90, sf::Color::Green),
            ColorButton(1600, 375, 160, 90, sf::Color::Blue)
        };

        static ColorButtonManager colorButtonManager;
        for (size_t i = 0; i < nColorButtons; i++){
            colorButtonManager.addColorButton(colorButtons[i]);   
        }

        static SizeButton sizeButton(1600, 805, 160, 90);
        static SizeButtonManager sizeButtonManager(sizeButton);

        static ToolPalette toolPalette(275, 130, 400, 30);

        pluginEraser =  (new PluginEraser(new Eraser(),
                                        new Props(&colorButtonManager, &sizeButtonManager, toolPalette),
                                        new ToolButton(100, 330, 135, 90, "images/eraser.png")));
        ((ToolButton*) pluginEraser->get_tool_button())->set_plugin((PluginEraser*) pluginEraser);

        return pluginEraser;
    }

    void destroy_plugin() {
        delete pluginEraser->get_tool_button();
        delete pluginEraser->get_props();
        delete pluginEraser->get_tool();
        delete pluginEraser;
    }
}
