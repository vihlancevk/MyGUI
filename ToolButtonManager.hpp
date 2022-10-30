#ifndef TOOL_BUTTON_MANAGER_HPP_
#define TOOL_BUTTON_MANAGER_HPP_

#include "Tool.hpp"
#include "ToolButton.hpp"

class ToolButtonManager {
    public:
        size_t size_;
        size_t curSize_;
        ToolButton** toolButtons_;

        Tool* activeTool_ = nullptr;
     public:
        ToolButtonManager(size_t size):
            size_(size),
            curSize_(0),
            toolButtons_((ToolButton**) new char[size_*sizeof(ToolButton*)])
            {}
        ~ToolButtonManager() {
            // TODO: wtire destructor
        }

        // TODO: write a copy constructor and assignment operator
        // ToolButtonManager(const ToolButtonManager& toolButtonManager):
        //     size_(toolButtonManager.size_),
        //     curSize_(toolButtonManager.curSize_),
        //     toolButtons_((ToolButton**) new char[size_*sizeof(ToolButton*)])
        //     {
        //         for (size_t i = 0; i < size_; i ++) {
        //             new (toolButtons_[i]) ToolButton(*toolButtonManager.toolButtons_[i]);
        //         }
        //     }
        // ToolButtonManager& operator = (const ToolButtonManager& toolButtonManager) {
        //     this->~ToolButtonManager();
            
        //     size_ = toolButtonManager.size_;
        //     curSize_ = toolButtonManager.curSize_;
        //     toolButtons_ = (ToolButton**) new char[size_*sizeof(ToolButton*)];
        //     for (size_t i = 0; i < size_; i ++) {
        //         new (toolButtons_[i]) ToolButton(*(toolButtonManager.toolButtons_[i]));
        //     }

        //     return *this;
        // }

        size_t addTool(ToolButton* toolButton) {
            if (curSize_ > size_) {
                std::cout << "Array of buttons is full!\n";
                return 0;
            } else {
                toolButtons_[curSize_++] = toolButton;
                return 1;
            }
        }

        void onMouseClick(unsigned x, unsigned y) {
            bool isActivated = false;
            
            for (size_t i = 0; i < size_; i++) {
                if (!toolButtons_[i]->isActive_)
                    isActivated = true;
                
                toolButtons_[i]->onMouseClick(x, y);

                if (toolButtons_[i]->isActive_ && isActivated) {
                    activeTool_ = toolButtons_[i]->tool_;

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

        void onMouseReleased(unsigned, unsigned) {}

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < size_; i++) {
                toolButtons_[i]->draw(window);
            }
        }
};

#endif // TOOL_BUTTON_MANAGER_HPP_
