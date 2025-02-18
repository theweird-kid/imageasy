#include "canvas_widget.hpp"
#include <cstdint>
#include <imgui.h>

CanvasWidget::CanvasWidget()
    : imageLoaded(false), imageTexture(0), imageWidth(0), imageHeight(0)
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
            ImGui::Text("Loaded Image:");
            ImGui::Image((void*)(intptr_t)imageTexture, ImVec2(imageWidth, imageHeight));
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
