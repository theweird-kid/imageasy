#ifndef GUI_HPP
#define GUI_HPP

#include <imgui.h>
#include "../backends/imgui_impl_glfw.h"
#include "../backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "widget.hpp"

class Gui {
public:
    explicit Gui(GLFWwindow* window) noexcept;
    ~Gui();
    void newFrame();
    void render();
    void addWidget(std::shared_ptr<Widget> widget);

private:
    void setupImGui();
    void cleanImGui();

    std::vector<std::shared_ptr<Widget>> widgets;
};

#endif // GUI_HPP
