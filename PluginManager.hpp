#ifndef PLUGIN_MANAGER_HPP_
#define PLUGIN_MANAGER_HPP_

#include "plugin.h"

class PluginManager {
    public:
        size_t size_;
        size_t curSize_;
        IPlugin** plugins_;

        ITool* activeTool_ = nullptr;
     public:
        PluginManager(size_t size):
            size_(size),
            curSize_(0),
            plugins_((IPlugin**) new char[size_*sizeof(IPlugin*)])
            {}
        ~PluginManager() {
            delete [] (char*) plugins_;
        }

        // TODO: write a copy constructor and assignment operator
        PluginManager(const PluginManager& pluginManager) = delete;
        PluginManager& operator = (const PluginManager& pluginManager) = delete;

        size_t addPlugin(IPlugin* plugin) {
            if (curSize_ >= size_) {
                std::cout << "Array of plugins is full!\n";
                return 0;
            } else {
                plugins_[curSize_++] = plugin;
                return 1;
            }
        }

        void on_mouse_press(Pair<int> point) {
            for (size_t i = 0; i < curSize_; i++) {
                plugins_[i]->get_props()->on_mouse_press(point);
            }

            bool isActivated = false;
            
            for (size_t i = 0; i < curSize_; i++) {
                if (!plugins_[i]->get_tool_button()->get_state())
                    isActivated = true;
                
                plugins_[i]->get_tool_button()->on_mouse_press(point);

                if (plugins_[i]->get_tool_button()->get_state() && isActivated) {
                    activeTool_ = plugins_[i]->get_tool();
                    plugins_[i]->get_tool_button()->set_signal(nullptr);

                    for (size_t j = 0; j < size_; j++) {
                        if (j != i)
                            plugins_[i]->get_tool_button()->set_state(false);
                    }

                    return;
                } else if (!(plugins_[i]->get_tool_button()->get_state() || isActivated)) {
                    activeTool_ = nullptr;
                    plugins_[i]->get_tool_button()->set_signal(nullptr);
                } else {
                    isActivated = false;
                }
            }
        }

        void on_mouse_release(Pair<int> point) {
            for (size_t i = 0; i < curSize_; i++) {
                plugins_[i]->get_props()->on_mouse_release(point);
            }
        }

        void on_mouse_move(Pair<int> point) {
            for (size_t i = 0; i < curSize_; i++) {
                plugins_[i]->get_props()->on_mouse_move(point);
            }
        }

        void draw(unsigned int* screen, int width, int height) {
            for (size_t i = 0; i < curSize_; i++) {
                plugins_[i]->get_props()->draw(screen, width, height);
                plugins_[i]->get_tool_button()->draw(screen, width, height);
            }
        }
};

#endif // PLUGIN_MANAGER_HPP_
