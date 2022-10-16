#ifndef WIDGET_MANAGER_HPP_
#define WIDGET_MANAGER_HPP_

#include "ButtonManager.hpp"
#include "CanvasWindow.hpp"

class WidgetManager {
    public:
        ButtonManager buttonManager_;
        CanvasWindow canvasWindow_;
    public:
        WidgetManager(ButtonManager buttonManager, CanvasWindow canvasWindow):
            buttonManager_(buttonManager),
            canvasWindow_(canvasWindow)
            {}
        ~WidgetManager() {}

        void onMouseClick(unsigned x, unsigned y) {
            buttonManager_.onMouseClick(x, y);

            canvasWindow_.paintbrushColor_ = buttonManager_.curColor_;
            
            canvasWindow_.onMouseClick(x, y);
        }

        void draw(sf::RenderWindow& window) {
            buttonManager_.draw(window);

            canvasWindow_.draw(window);
        }
};

#endif // WIDGET_MANAGER_HPP_
