#ifndef WIDGET_MANAGER_HPP_
#define WIDGET_MANAGER_HPP_

#include "ColorButtonManager.hpp"
#include "ToolButtonManager.hpp"
#include "CanvasWindow.hpp"

class PainterManager {
    public:
        ColorButtonManager colorButtonManager_;
        ToolButtonManager toolButtonManager_;
        CanvasWindow canvasWindow_;
    public:
        PainterManager(ColorButtonManager& colorButtonManager, ToolButtonManager& toolButtonManager, CanvasWindow& canvasWindow):
            colorButtonManager_(colorButtonManager),
            toolButtonManager_(toolButtonManager),
            canvasWindow_(canvasWindow)
            {}
        ~PainterManager() {}

        void onMouseMove(unsigned x, unsigned y) {
            canvasWindow_.onMouseMove(x, y);
        }

        void onMouseClick(unsigned x, unsigned y) {
            colorButtonManager_.onMouseClick(x, y);

            // toolButtonManager_.color_ = colorButtonManager_.activeColor_;
            toolButtonManager_.onMouseClick(x, y);

            canvasWindow_.activeTool_ = toolButtonManager_.activeTool_;
            canvasWindow_.onMouseClick(x, y);
        }

        void onMouseReleased(unsigned x, unsigned y) {
            colorButtonManager_.onMouseReleased(x, y);
            toolButtonManager_.onMouseReleased(x, y);
            canvasWindow_.onMouseReleased(x, y);
        }

        void draw(sf::RenderWindow& window) {
            colorButtonManager_.draw(window);
            toolButtonManager_.draw(window);
            canvasWindow_.draw(window);
        }
};

#endif // WIDGET_MANAGER_HPP_
