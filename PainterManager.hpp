#ifndef WIDGET_MANAGER_HPP_
#define WIDGET_MANAGER_HPP_

#include "ButtonManager.hpp"
#include "ToolManager.hpp"
#include "CanvasWindow.hpp"

class PainterManager {
    public:
        ButtonManager buttonManager_;
        ToolManager* toolManager_; // ptr on ToolManager object, that create in main.cpp
        CanvasWindow canvasWindow_;
    public:
        PainterManager(ButtonManager buttonManager, ToolManager* toolManager, CanvasWindow canvasWindow):
            buttonManager_(buttonManager),
            toolManager_(toolManager),
            canvasWindow_(canvasWindow)
            {}
        ~PainterManager() {}

        void onMouseMove(unsigned x, unsigned y) {
            canvasWindow_.onMouseMove(x, y);
        }

        void onMouseClick(unsigned x, unsigned y) {
            buttonManager_.onMouseClick(x, y);

            toolManager_->color_ = buttonManager_.curColor_;
            toolManager_->onMouseClick(x, y);

            canvasWindow_.activeTool_ = toolManager_->activeTool_;
            canvasWindow_.onMouseClick(x, y);
        }

        void onMouseReleased(unsigned x, unsigned y) {
            buttonManager_.onMouseReleased(x, y);
            toolManager_->onMouseReleased(x, y);
            canvasWindow_.onMouseReleased(x, y);
        }

        void draw(sf::RenderWindow& window) {
            buttonManager_.draw(window);
            toolManager_->draw(window);
            canvasWindow_.draw(window);
        }
};

#endif // WIDGET_MANAGER_HPP_
