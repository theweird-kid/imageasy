
#include "./tools/blur_image_tool.hpp"
#include "./tools/load_image_tool.hpp"
#include <imgui.h>
#include "gui.hpp"

Gui::Gui(GLFWwindow* window) noexcept {
    setupImGui(window);

    // Create and add widgets
    canvasWidget = std::make_shared<CanvasWidget>();
    toolCanvas = std::make_unique<ToolCanvas>(canvasWidget);

    // Add tools to the tool canvas
    toolCanvas->addTool(std::make_shared<LoadImageTool>(canvasWidget));
    toolCanvas->addTool(std::make_shared<BlurImageTool>(canvasWidget));
}

Gui::~Gui() {
    cleanImGui();
}

void Gui::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::render() {
    // Render the canvas widget
    ImGui::SetNextWindowSize(ImVec2(1350, 1000), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(550, 10), ImGuiCond_Always);
    canvasWidget->render();

    // Render the tool canvas
    ImGui::SetNextWindowSize(ImVec2(500, 1000), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    toolCanvas->render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::setupImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Gui::cleanImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
