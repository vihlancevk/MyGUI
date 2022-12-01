#ifndef WIDGET_MANAGER_HPP_
#define WIDGET_MANAGER_HPP_

#include "PluginManager.hpp"
#include "CurvesFilterWindow.hpp"
#include "CanvasWindow.hpp"

class PainterManager {
    public:
        PluginManager& pluginManager_;
        CurvesFilterWindow& curvesFilterWindow_;
        CanvasWindow& canvasWindow_;
    public:
        PainterManager(PluginManager& pluginManager, CurvesFilterWindow& curvesFilterWindow,
                       CanvasWindow& canvasWindow):
            pluginManager_(pluginManager),
            curvesFilterWindow_(curvesFilterWindow),
            canvasWindow_(canvasWindow)
            {}
        ~PainterManager() {}

        void on_mouse_press(Pair<int> point) {
            pluginManager_.on_mouse_press(point);
            
            curvesFilterWindow_.on_mouse_press(point);

            canvasWindow_.activeTool_ = pluginManager_.activeTool_;
            canvasWindow_.on_mouse_press(point);
        }

        void on_mouse_release(Pair<int> point) {
            pluginManager_.on_mouse_release(point);

            canvasWindow_.on_mouse_release(point);
        }

        void on_mouse_move(Pair<int> point) {
            pluginManager_.on_mouse_move(point);
            
            canvasWindow_.on_mouse_move(point);
        }

        void on_key_press(int key) {
            curvesFilterWindow_.on_key_press(key);
        }

        void draw(unsigned int* screen, int width, int height) {            
            pluginManager_.draw(screen, width, height);
            
            canvasWindow_.draw(screen, width, height);
        
            curvesFilterWindow_.draw(screen, width, height);
        }
};

#endif // WIDGET_MANAGER_HPP_
