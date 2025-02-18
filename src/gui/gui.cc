#include "gui.hpp"
#include "load_image_tool.hpp"

Gui::Gui(GLFWwindow* window) noexcept {
    setupImGui(window);

    // Create and add widgets
    canvasWidget = std::make_shared<CanvasWidget>();
    toolCanvas = std::make_unique<ToolCanvas>(canvasWidget);

    // Add tools to the tool canvas
    toolCanvas->addTool(std::make_shared<LoadImageTool>(canvasWidget));
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
    canvasWidget->render();

    // Render the tool canvas
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
