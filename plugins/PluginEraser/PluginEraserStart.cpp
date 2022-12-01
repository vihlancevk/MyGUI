#include "plugin.h"
#include "Eraser.hpp"
#include "SizeButton.hpp"
#include "SizeButtonManager.hpp"
#include "EraserPalette.hpp"
#include "PropsEraser.hpp"
#include "EraserButton.hpp"

static IPlugin* pluginEraser = nullptr;

IPlugin* get_plugin() {
    static SizeButton sizeButton(1600, 805, 160, 90);
    static SizeButtonManager sizeButtonManager(sizeButton);

    static ToolPalette toolPalette(275, 130, 400, 30);

    pluginEraser =  (new PluginEraser(new Eraser(),
                                      new Props(&sizeButtonManager, toolPalette),
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
