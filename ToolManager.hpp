#ifndef TOOL_MANAGER_HPP_
#define TOOL_MANAGER_HPP_

#include <iostream>
#include "Tool.hpp"
#include "ToolPalette.hpp"

class ToolManager {
    public:
        size_t size_;
        size_t curSize_;
        Tool** tools_;
        ToolPalette& toolPalette_;

        Tool* activeTool_ = nullptr; 
        unsigned activeSize_ = 10;
        sf::Color activeColor_ = sf::Color::Black;
     public:
        ToolManager(unsigned size, ToolPalette& toolPalette):
            size_(size),
            curSize_(0),
            tools_((Tool**) new char[size_*sizeof(Tool*)]),
            toolPalette_(toolPalette)
            {}
        ~ToolManager() {
            delete [] (char*) tools_;
        }

        ToolManager(const ToolManager& toolManager) = delete;
        ToolManager& operator = (const ToolManager& toolManager) = delete;

        bool addTool(Tool* tool) {
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
                activeTool_->size_ = activeSize_;
                activeTool_->color_ = activeColor_;
            }
        }

        void draw(unsigned int* screen, int width, int height) {
            toolPalette_.setTool(activeTool_);
            toolPalette_.draw(screen, width, height);
        }
};

#endif // TOOL_MANAGER_HPP_
