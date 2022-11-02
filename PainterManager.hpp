#ifndef WIDGET_MANAGER_HPP_
#define WIDGET_MANAGER_HPP_

#include "ToolManager.hpp"
#include "ColorButtonManager.hpp"
#include "ToolButtonManager.hpp"
#include "CanvasWindow.hpp"

class PainterManager {
    public:
        ToolManager& toolManager_;
        ColorButtonManager& colorButtonManager_;
        ToolButtonManager& toolButtonManager_;
        CanvasWindow& canvasWindow_;
    public:
        PainterManager(ToolManager& toolManager, ColorButtonManager& colorButtonManager,
                       ToolButtonManager& toolButtonManager, CanvasWindow& canvasWindow):
            toolManager_(toolManager),
            colorButtonManager_(colorButtonManager),
            toolButtonManager_(toolButtonManager),
            canvasWindow_(canvasWindow)
            {}
        ~PainterManager() {}

        void onMouseMove(unsigned x, unsigned y) {
            colorButtonManager_.onMouseMove(x, y);
            canvasWindow_.onMouseMove(x, y);
        }

        void onMouseClick(unsigned x, unsigned y) {
            colorButtonManager_.onMouseClick(x, y);
            toolButtonManager_.onMouseClick(x, y);

            toolManager_.activeColor_ = colorButtonManager_.activeColor_;
            toolManager_.activeTool_ = toolButtonManager_.activeTool_;
            toolManager_.setParametersOfActiveTool();

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
