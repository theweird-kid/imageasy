#ifndef IMAGE_LOADER_WIDGET_HPP
#define IMAGE_LOADER_WIDGET_HPP

#include "widget.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <stb_image.h>
#include <tinyfiledialogs.h>

class ImageLoaderWidget : public Widget {
public:
    ImageLoaderWidget();
    ~ImageLoaderWidget();
    void render() override;
    bool isImageLoaded() const;
    GLuint getImageTexture() const;
    int getImageWidth() const;
    int getImageHeight() const;

private:
    void loadImage(const char* path);
    GLuint imageTexture;
    int imageWidth, imageHeight;
    bool imageLoaded;
};

#endif // IMAGE_LOADER_WIDGET_HPP
