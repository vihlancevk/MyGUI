#ifndef WIDGET_MANAGER_HPP_
#define WIDGET_MANAGER_HPP_

#include "ToolManager.hpp"
#include "ColorButtonManager.hpp"
#include "SizeButtonManager.hpp"
#include "ToolButtonManager.hpp"
#include "CurvesFilterWindow.hpp"
#include "CanvasWindow.hpp"

class PainterManager {
    public:
        ToolManager& toolManager_;
        ColorButtonManager& colorButtonManager_;
        SizeButtonManager& sizeButtonManager_;
        ToolButtonManager& toolButtonManager_;
        CurvesFilterWindow& curvesFilterWindow_;
        CanvasWindow& canvasWindow_;
    public:
        PainterManager(ToolManager& toolManager, ColorButtonManager& colorButtonManager,
                       SizeButtonManager& sizeButtonManager, ToolButtonManager& toolButtonManager,
                       CurvesFilterWindow& curvesFilterWindow, CanvasWindow& canvasWindow):
            toolManager_(toolManager),
            colorButtonManager_(colorButtonManager),
            sizeButtonManager_(sizeButtonManager),
            toolButtonManager_(toolButtonManager),
            curvesFilterWindow_(curvesFilterWindow),
            canvasWindow_(canvasWindow)
            {}
        ~PainterManager() {}

        void onMouseMove(unsigned x, unsigned y) {
            colorButtonManager_.onMouseMove(x, y);
            sizeButtonManager_.onMouseMove(x, y);
            canvasWindow_.onMouseMove(x, y);
        }

        void onMouseClick(unsigned x, unsigned y) {
            colorButtonManager_.onMouseClick(x, y);
            sizeButtonManager_.onMouseClick(x, y);
            toolButtonManager_.onMouseClick(x, y);
            curvesFilterWindow_.onMouseClick(x, y);
            canvasWindow_.activeTool_ = toolButtonManager_.activeTool_;
            canvasWindow_.onMouseClick(x, y);
        }

        void onMouseReleased(unsigned x, unsigned y) {
            colorButtonManager_.onMouseReleased(x, y);
            sizeButtonManager_.onMouseReleased(x, y);
            toolButtonManager_.onMouseReleased(x, y);

            toolManager_.activeColor_ = colorButtonManager_.activeColor_;
            toolManager_.activeSize_ = sizeButtonManager_.activeSize_;
            toolManager_.activeTool_ = toolButtonManager_.activeTool_;
            toolManager_.setParametersOfActiveTool();

            canvasWindow_.onMouseReleased(x, y);
        }

        void onKeyboard(int code) {
            curvesFilterWindow_.onKeyboard(code);
        }

        void draw(sf::RenderWindow& window) {
            toolManager_.draw(window);
            colorButtonManager_.draw(window);
            sizeButtonManager_.draw(window);
            toolButtonManager_.draw(window);
            canvasWindow_.draw(window);
            curvesFilterWindow_.draw(window);
        }
};

#endif // WIDGET_MANAGER_HPP_
