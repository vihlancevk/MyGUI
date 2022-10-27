#ifndef TOOL_MANAGER_HPP_
#define TOOL_MANAGER_HPP_

#include <vector>
#include "Tool.hpp"

class ToolManager {
    public:
        std::vector<Tool*> tools_;

        Color color_ = Color::BLACK;
        Tool* activeTool_ = nullptr;
     public:
        ToolManager():
            tools_()
            {}
        ~ToolManager() {
            for (size_t i = 0; i < tools_.size(); i++) {
                delete tools_[i];
            }
        }

        void addTool(Tool* ptool) {
            tools_.push_back(ptool);
        }

        void onMouseClick(unsigned x, unsigned y) {
            bool isActivated = false;
            
            for (size_t i = 0; i < tools_.size(); i++) {
                tools_[i]->color_ = color_;
                
                if (!tools_[i]->isActive_)
                    isActivated = true;
                
                tools_[i]->onMouseClick(x, y);

                if (tools_[i]->isActive_ && isActivated) {
                    for (size_t j = 0; j < tools_.size(); j++) {
                        if (j != i)
                            tools_[j]->isActive_ = false;
                    }

                    activeTool_ = tools_[i];
                    return;
                } else {
                    isActivated = false;
                }
            }
        }

        void onMouseReleased(unsigned, unsigned) {}

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < tools_.size(); i++) {
                tools_[i]->draw(window);
            }
        }
};

#endif // TOOL_MANAGER_HPP_
