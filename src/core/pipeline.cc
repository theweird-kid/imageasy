#include "pipeline.hpp"
#include <iostream>

Pipeline::Pipeline()
    : imageLoaded(false), originalImageTexture(0), processedImageTexture(0),
    imageWidth(0), imageHeight(0)
{}

Pipeline::~Pipeline() {
    if (imageLoaded) {
        glDeleteTextures(1, &originalImageTexture);
        glDeleteTextures(1, &processedImageTexture);
    }
}

void Pipeline::setImage(GLuint texture, int width, int height) {
    clearImage();

    std::cout << "Image Changed\n";
    originalImageTexture = texture;
    imageWidth = width;
    imageHeight = height;
    imageLoaded = true;

    // Create a copy of the original image for processing
    glGenTextures(1, &processedImageTexture);
    glBindTexture(GL_TEXTURE_2D, processedImageTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Copy the original image to the processed image
    glCopyImageSubData(originalImageTexture, GL_TEXTURE_2D, 0, 0, 0, 0,
                       processedImageTexture, GL_TEXTURE_2D, 0, 0, 0, 0,
                       width, height, 1);
}

void Pipeline::applyEffect(const std::function<void(GLuint, GLuint, int, int)>& effect) {
    if (!imageLoaded) return;

    // Apply the effect to the processed image
    effect(originalImageTexture, processedImageTexture, imageWidth, imageHeight);
}

void Pipeline::clearImage() {
    if (imageLoaded) {
        glDeleteTextures(1, &originalImageTexture);
        glDeleteTextures(1, &processedImageTexture);
        imageLoaded = false;
        originalImageTexture = 0;
        processedImageTexture = 0;
        imageWidth = 0;
        imageHeight = 0;
    }
}

bool Pipeline::isImageLoaded() const {
    return imageLoaded;
}

GLuint Pipeline::getOriginalImageTexture() const {
    return originalImageTexture;
}

GLuint Pipeline::getProcessedImageTexture() const {
    return processedImageTexture;
}

int Pipeline::getImageWidth() const {
    return imageWidth;
}

int Pipeline::getImageHeight() const {
    return imageHeight;
}
