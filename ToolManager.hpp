#ifndef TOOL_MANAGER_HPP_
#define TOOL_MANAGER_HPP_

#include <iostream>
#include "plugin.h"
#include "ToolPalette.hpp"

class ToolManager {
    public:
        size_t size_;
        size_t curSize_;
        ITool** tools_;
        ToolPalette& toolPalette_;

        ITool* activeTool_ = nullptr; 
        unsigned activeSize_ = 10;
        sf::Color activeColor_ = sf::Color::Black;
     public:
        ToolManager(unsigned size, ToolPalette& toolPalette):
            size_(size),
            curSize_(0),
            tools_((ITool**) new char[size_*sizeof(ITool*)]),
            toolPalette_(toolPalette)
            {}
        ~ToolManager() {
            delete [] (char*) tools_;
        }

        ToolManager(const ToolManager& toolManager) = delete;
        ToolManager& operator = (const ToolManager& toolManager) = delete;

        bool addTool(ITool* tool) {
            if (curSize_ >= size_) {
                std::cout << "Array of Tool is full!\n";
                return 0;
            } else {
                tools_[curSize_++] = tool;
                return 1;
            }
        }

        void setParametersOfActiveTool() {
            if (activeTool_) {
                toolPalette_.setSize(activeSize_);
                toolPalette_.setColor(activeColor_);
                toolPalette_.setState(true);
            } else {
                toolPalette_.setState(false);
            }
        }

        void draw(unsigned int* screen, int width, int height) {
            toolPalette_.draw(screen, width, height);
        }
};

#endif // TOOL_MANAGER_HPP_
