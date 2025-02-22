#ifndef GUI_HPP
#define GUI_HPP

#include "tool_canvas.hpp"
#include <imgui.h>
#include "../backends/imgui_impl_glfw.h"
#include "../backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "widget.hpp"
#include "canvas_widget.hpp"

class Gui {
public:
    explicit Gui(GLFWwindow* window) noexcept;
    ~Gui();
    void newFrame();
    void render();

private:
    void setupImGui(GLFWwindow* window);
    void cleanImGui();

    std::shared_ptr<CanvasWidget> canvasWidget;
    std::unique_ptr<ToolCanvas> toolCanvas;
};

#endif // GUI_HPP
