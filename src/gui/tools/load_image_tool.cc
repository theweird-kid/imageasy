#include "load_image_tool.hpp"
#include <imgui.h>
#include <tinyfiledialogs.h>
#include <stb_image.h>
#include <GL/gl.h>
#include <iostream>

LoadImageTool::LoadImageTool(std::shared_ptr<CanvasWidget> canvas)
    : canvas(canvas)
{}

void LoadImageTool::render() {
    if (ImGui::Button("Load Image")) {
        loadImage();
    }
    ImGui::SameLine();

    // Set custom color for the "Remove Image" button
    ImVec4 buttonColor = ImVec4(0.8f, 0.1f, 0.1f, 1.0f); // Red color
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

    if (ImGui::Button("Remove Image")) {
        removeImage();
    }

    ImGui::PopStyleColor(3); // Restore previous colors
}

void LoadImageTool::loadImage() {
    const char* filePath = tinyfd_openFileDialog("Select Image", "", 0, nullptr, nullptr, 0);
    if (filePath) {
        int width, height, channels;
        unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);
        if (data) {
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA : GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(data);
            canvas->setImage(texture, width, height);
        } else {
            std::cerr << "Failed to load image: " << filePath << std::endl;
        }
    }
}

void LoadImageTool::removeImage() {
    canvas->clearImage();
}
