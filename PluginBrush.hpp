#ifndef PLUGIN_BRUSH_HPP_
#define PLUGIN_BRUSH_HPP_

#include "plugin.h"

class PluginBrush: public IPlugin {
    public:
        PluginBrush(ITool* tool, IWidget* props, IPushButton* tool_button) {
             set_tool(tool);
             set_props(props);
             set_tool_button(tool_button);
        }
};

#endif // PLUGIN_BRUSH_HPP_
