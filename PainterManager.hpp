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

        void on_mouse_press(Pair<int> point) {
            colorButtonManager_.on_mouse_press(point);
            sizeButtonManager_.on_mouse_press(point);
            toolButtonManager_.on_mouse_press(point);
            curvesFilterWindow_.on_mouse_press(point);
            canvasWindow_.activeTool_ = toolButtonManager_.activeTool_;
            canvasWindow_.on_mouse_press(point);
        }

        void on_mouse_release(Pair<int> point) {
            colorButtonManager_.on_mouse_release(point);
            sizeButtonManager_.on_mouse_release(point);
            toolButtonManager_.on_mouse_release(point);

            toolManager_.activeColor_ = colorButtonManager_.activeColor_;
            toolManager_.activeSize_ = sizeButtonManager_.activeSize_;
            toolManager_.activeTool_ = toolButtonManager_.activeTool_;
            toolManager_.setParametersOfActiveTool();

            canvasWindow_.on_mouse_release(point);
        }

        void on_mouse_move(Pair<int> point) {
            colorButtonManager_.on_mouse_move(point);
            sizeButtonManager_.on_mouse_move(point);
            canvasWindow_.on_mouse_move(point);
        }

        void on_key_press(int key) {
            curvesFilterWindow_.on_key_press(key);
        }

        void draw(unsigned int* screen, int width, int height) {
            toolManager_.draw(screen, width, height);
            colorButtonManager_.draw(screen, width, height);
            sizeButtonManager_.draw(screen, width, height);
            toolButtonManager_.draw(screen, width, height);
            canvasWindow_.draw(screen, width, height);
            curvesFilterWindow_.draw(screen, width, height);
        }
};

#endif // WIDGET_MANAGER_HPP_
