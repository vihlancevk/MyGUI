#ifndef TOOL_MANAGER_HPP_
#define TOOL_MANAGER_HPP_

#include <iostream>
#include "Tool.hpp"

class ToolManager {
    public:
        size_t size_;
        size_t curSize_;
        Tool** tools_;

        Tool* activeTool_ = nullptr; 
        unsigned activeSize_ = 10;
        Color activeColor_ = Color::BLACK;
     public:
        ToolManager(unsigned size):
            size_(size),
            curSize_(0),
            tools_((Tool**) new char[size_*sizeof(Tool*)])
            {}
        ~ToolManager() {
            delete (char*) tools_;
        }

        // TODO: write a copy constructor and assignment operator
        ToolManager(const ToolManager& toolManager):
            size_(toolManager.size_),
            curSize_(toolManager.curSize_),
            tools_((Tool**) new char[size_*sizeof(Tool*)])
            {
                for (size_t i = 0; i < curSize_; i ++) {
                    tools_[i] = toolManager.tools_[i];
                }
            }
        ToolManager& operator = (const ToolManager& toolManager) {
            this->~ToolManager();

            size_ = toolManager.size_;
            curSize_ = toolManager.curSize_;
            tools_ = (Tool**) new char[size_*sizeof(Tool*)];
            for (size_t i = 0; i < curSize_; i ++) {
                tools_[i] = toolManager.tools_[i];
            }

            return *this;
        }

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
            activeTool_->size_ = activeSize_;
            activeTool_->color_ = activeColor_;
        }
};

#endif // TOOL_MANAGER_HPP_
