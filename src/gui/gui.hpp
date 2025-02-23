#ifndef GUI_HPP
#define GUI_HPP

#include <memory>

#include "tool_canvas.hpp"
#include <GLFW/glfw3.h>
#include "../core/pipeline.hpp"
#include "canvas_widget.hpp"


class Gui {
public:
    Gui(GLFWwindow* window);
    ~Gui();

    void newFrame();
    void render();

private:
    void setupImGui(GLFWwindow* window);
    void cleanupImGui();

    std::shared_ptr<Pipeline> pipeline;
    std::unique_ptr<CanvasWidget> canvasWidget;
    std::unique_ptr<ToolCanvas> toolCanvas;
};

#endif // GUI_HPP
