#ifndef TOOL_MANAGER_HPP_
#define TOOL_MANAGER_HPP_

#include <vector>
#include "Tool.hpp"

class ToolManager {
    public:
        std::vector<Tool*> tools_;
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

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < tools_.size(); i++) {
                tools_[i]->draw(window);
            }
        }
};

#endif // TOOL_MANAGER_HPP_
