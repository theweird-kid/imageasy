#include "gui.hpp"
#include <imgui.h>
#include "../core/blur_effect.hpp"
#include "../core/contrast_effect.hpp"
#include "../backends/imgui_impl_glfw.h"
#include "../backends/imgui_impl_opengl3.h"

Gui::Gui(GLFWwindow* window) {
    setupImGui(window);

    pipeline = std::make_shared<Pipeline>();
    canvasWidget = std::make_unique<CanvasWidget>(pipeline);
    toolCanvas = std::make_unique<ToolCanvas>(pipeline);

    // Add Effects
    auto blurEffect = std::make_shared<BlurEffect>("src/core/shaders/blur_horizontal.glsl", "src/core/shaders/blur_vertical.glsl");
    toolCanvas->addImageEffect(blurEffect, "Blur");

    auto contrastEffect = std::make_shared<ContrastEffect>("src/core/shaders/contrast_compute.glsl");
    toolCanvas->addImageEffect(contrastEffect, "Contrast");
}

Gui::~Gui() {
    cleanupImGui();
}

void Gui::render() {
    canvasWidget->render();
    toolCanvas->render();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::setupImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Gui::cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
