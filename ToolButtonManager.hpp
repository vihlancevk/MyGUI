#ifndef TOOL_BUTTON_MANAGER_HPP_
#define TOOL_BUTTON_MANAGER_HPP_

#include "Tool.hpp"
#include "ToolButton.hpp"

class ToolButtonManager {
    public:
        size_t size_;
        size_t curSize_;
        ToolButton** toolButtons_;

        ITool* activeTool_ = nullptr;
     public:
        ToolButtonManager(size_t size):
            size_(size),
            curSize_(0),
            toolButtons_((ToolButton**) new char[size_*sizeof(ToolButton*)])
            {}
        ~ToolButtonManager() {
            delete [] (char*) toolButtons_;
        }

        // TODO: write a copy constructor and assignment operator
        ToolButtonManager(const ToolButtonManager& toolButtonManager) = delete;
        ToolButtonManager& operator = (const ToolButtonManager& toolButtonManager) = delete;

        size_t addTool(ToolButton* toolButton) {
            if (curSize_ >= size_) {
                std::cout << "Array of buttons is full!\n";
                return 0;
            } else {
                toolButtons_[curSize_++] = toolButton;
                return 1;
            }
        }

        void on_mouse_press(Pair<int> point) {
            bool isActivated = false;
            
            for (size_t i = 0; i < curSize_; i++) {
                if (!toolButtons_[i]->isActive_)
                    isActivated = true;
                
                toolButtons_[i]->on_mouse_press(point);

                if (toolButtons_[i]->isActive_ && isActivated) {
                    activeTool_ = *toolButtons_[i]->tool_;

                    for (size_t j = 0; j < size_; j++) {
                        if (j != i)
                            toolButtons_[j]->isActive_ = false;
                    }

                    return;
                } else if (!(toolButtons_[i]->isActive_ || isActivated)) {
                    activeTool_ = nullptr;
                } else {
                    isActivated = false;
                }
            }
        }

        void on_mouse_release(Pair<int> /*point*/) {
            std::cout << "ToolButtonManager::on_mouse_release(Pair<int>)\n";
        }

        void draw(unsigned int* screen, int width, int height) {
            for (size_t i = 0; i < curSize_; i++) {
                toolButtons_[i]->draw(screen, width, height);
            }
        }
};

#endif // TOOL_BUTTON_MANAGER_HPP_
