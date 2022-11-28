#ifndef PLUGIN_ERASER_HPP_
#define PLUGIN_ERASER_HPP_

#include "plugin.h"

class PluginEraser: public IPlugin {
    public:
        PluginEraser(ITool* tool, IWidget* props, IPushButton* tool_button)
            // IPlugin()
            {
                set_tool(tool);
                set_props(props);
                set_tool_button(tool_button);
            }

        ~PluginEraser() {}
};

#endif // PLUGIN_ERASER_HPP_
