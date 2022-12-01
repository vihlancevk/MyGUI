#include "plugin.h"
#include "Brush.hpp"
#include "ColorButton.hpp"
#include "ColorButtonManager.hpp"
#include "SizeButton.hpp"
#include "SizeButtonManager.hpp"
#include "BrushPalette.hpp"
#include "PropsBrush.hpp"
#include "BrushButton.hpp"

static IPlugin* pluginBrush = nullptr;

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

    pluginBrush =  (new PluginBrush(new Brush(),
                                    new Props(&colorButtonManager, &sizeButtonManager, toolPalette),
                                    new ToolButton(100, 225, 135, 90, "images/brush.png")));
    ((ToolButton*) pluginBrush->get_tool_button())->set_plugin((PluginBrush*) pluginBrush);

    return pluginBrush;
}

void destroy_plugin() {
    delete pluginBrush->get_tool_button();
    delete pluginBrush->get_props();
    delete pluginBrush->get_tool();
    delete pluginBrush;
}
