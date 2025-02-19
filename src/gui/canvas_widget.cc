#include "canvas_widget.hpp"
#include <cstdint>
#include <imgui.h>

CanvasWidget::CanvasWidget()
    : imageLoaded(false), imageTexture(0),
    imageWidth(0), imageHeight(0), zoomFactor(1.0f)
{}

CanvasWidget::~CanvasWidget()
{
    if (imageLoaded) {
        glDeleteTextures(1, &imageTexture);
    }
}

void CanvasWidget::render() {
    if (ImGui::Begin("Canvas")) {
        if (imageLoaded) {
            // Capture mouse wheel input for zooming
            ImGuiIO& io = ImGui::GetIO();
            if (io.MouseWheel != 0.0f) {
                zoomFactor += io.MouseWheel * 0.1f;
                if (zoomFactor < 0.1f) zoomFactor = 0.1f; // Clamp zoom factor to a minimum value
                if (zoomFactor > 10.0f) zoomFactor = 10.0f; // Clamp zoom factor to a maximum value
            }

            // Calculate centered position
            ImVec2 windowSize = ImGui::GetContentRegionAvail();
            ImVec2 imageSize = ImVec2(imageWidth * zoomFactor, imageHeight * zoomFactor);
            ImVec2 imagePos = ImVec2((windowSize.x - imageSize.x) / 2.0f, (windowSize.y - imageSize.y) / 2.0f);

            // Add padding to avoid clipping
            ImGui::SetCursorPos(imagePos);

            ImGui::Image((void*)(intptr_t)imageTexture, imageSize);
        } else {
            ImGui::Text("No image loaded.");
        }
    }
    ImGui::End();
}

void CanvasWidget::setImage(GLuint texture, int width, int height) {
    imageTexture = texture;
    imageWidth = width;
    imageHeight = height;
    imageLoaded = true;
}

void CanvasWidget::clearImage() {
    if (imageLoaded) {
        glDeleteTextures(1, &imageTexture);
        imageLoaded = false;
        imageTexture = 0;
        imageWidth = 0;
        imageHeight = 0;
    }
}

bool CanvasWidget::isImageLoaded() const {
    return imageLoaded;
}

GLuint CanvasWidget::getImageTexture() const {
    return imageTexture;
}

int CanvasWidget::getImageWidth() const {
    return imageWidth;
}

int CanvasWidget::getImageHeight() const {
    return imageHeight;
}
