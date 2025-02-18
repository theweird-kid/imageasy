#include "image_loader_widget.hpp"
#include <imgui.h>

ImageLoaderWidget::ImageLoaderWidget()
    : imageLoaded(false), imageTexture(0), imageWidth(0), imageHeight(0) {}

ImageLoaderWidget::~ImageLoaderWidget() {
    if (imageLoaded) {
        glDeleteTextures(1, &imageTexture);
    }
}

void ImageLoaderWidget::render()
{
    if (ImGui::Begin("Image Loader")) {
        if (ImGui::Button("Load Image")) {
            const char* filePath = tinyfd_openFileDialog("Select Image", "", 0, nullptr, nullptr, 0);
            if (filePath) {
                loadImage(filePath);
            }
        }
        if (imageLoaded) {
            ImGui::Text("Loaded Image:");
            ImGui::Image((void*)(intptr_t)imageTexture, ImVec2(imageWidth, imageHeight));
        }
    }
    ImGui::End();
}

void ImageLoaderWidget::loadImage(const char* filePath)
{
    // Load image using stb_image
    int channels;
    unsigned char* data = stbi_load(filePath, &imageWidth, &imageHeight, &channels, 0);
    if(data)
    {
        // Ensure that the image texture is empty
        if(imageTexture) {
            glDeleteTextures(1, &imageTexture);
        }

        glGenTextures(1, &imageTexture);
        glBindTexture(GL_TEXTURE_2D, imageTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        imageLoaded = true;
    }
    else
    {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        imageLoaded = false;
    }
}

bool ImageLoaderWidget::isImageLoaded() const {
    return imageLoaded;
}

GLuint ImageLoaderWidget::getImageTexture() const {
    return imageTexture;
}

int ImageLoaderWidget::getImageWidth() const {
    return imageWidth;
}

int ImageLoaderWidget::getImageHeight() const {
    return imageHeight;
}
