#include "canvas_widget.hpp"
#include <GL/gl.h>
#include <cstdint>
#include <imgui.h>

CanvasWidget::CanvasWidget(std::shared_ptr<Pipeline> pipeline)
    : pipeline(pipeline), zoomFactor(1.0f)
{}

CanvasWidget::~CanvasWidget() {}

void CanvasWidget::render() {
    // Render original image window
    if (ImGui::Begin("Original Image"))
    {
        if (pipeline->isImageLoaded())
        {
            // Capture mouse wheel input for zooming
            ImGuiIO& io = ImGui::GetIO();
            if (io.MouseWheel != 0.0f) {
                zoomFactor += io.MouseWheel * 0.1f;
                if (zoomFactor < 0.1f) zoomFactor = 0.1f; // Clamp zoom factor to a minimum value
                if (zoomFactor > 10.0f) zoomFactor = 10.0f; // Clamp zoom factor to a maximum value
            }

            // Calculate image size
            ImVec2 windowSize = ImGui::GetContentRegionAvail();
            ImVec2 imageSize = ImVec2(pipeline->getImageWidth() * zoomFactor, pipeline->getImageHeight() * zoomFactor);

            // Display original image
            ImGui::Image((void*)(intptr_t)pipeline->getOriginalImageTexture(), imageSize);
        }
        else {
            ImGui::Text("No image loaded.");
        }
    }
    ImGui::End();

    // Render processed image window
    if (ImGui::Begin("Processed Image"))
    {
        if (pipeline->isImageLoaded())
        {
            // Capture mouse wheel input for zooming
            ImGuiIO& io = ImGui::GetIO();
            if (io.MouseWheel != 0.0f) {
                zoomFactor += io.MouseWheel * 0.1f;
                if (zoomFactor < 0.1f) zoomFactor = 0.1f; // Clamp zoom factor to a minimum value
                if (zoomFactor > 10.0f) zoomFactor = 10.0f; // Clamp zoom factor to a maximum value
            }

            // Calculate image size
            ImVec2 windowSize = ImGui::GetContentRegionAvail();
            ImVec2 imageSize = ImVec2(pipeline->getImageWidth() * zoomFactor, pipeline->getImageHeight() * zoomFactor);

            // Display processed image
            ImGui::Image((void*)(intptr_t)pipeline->getProcessedImageTexture(), imageSize);
        }
        else {
            ImGui::Text("No image loaded.");
        }
    }
    ImGui::End();
}

void CanvasWidget::clearImage() {
    pipeline->clearImage();
}
