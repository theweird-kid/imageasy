#include "tool_canvas.hpp"
#include <imgui.h>
#include <tinyfiledialogs.h>
#include <stb_image.h>
#include <GL/gl.h>
#include <iostream>

ToolCanvas::ToolCanvas(std::shared_ptr<CanvasWidget> canvas)
    : canvas(canvas)
{}

void ToolCanvas::render() {
    if (ImGui::Begin("Tools")) {
        for (auto& tool : tools) {
            tool->render();
        }
    }
    ImGui::End();
}

void ToolCanvas::addTool(std::shared_ptr<Widget> tool) {
    tools.push_back(tool);
}
