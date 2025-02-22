#ifndef CANVAS_WIDGET_HPP
#define CANVAS_WIDGET_HPP

#include "widget.hpp"
#include <GL/gl.h>

class CanvasWidget : public Widget {
public:
    CanvasWidget();
    ~CanvasWidget();
    void render() override;
    void setImage(GLuint texture, int width, int height);
    void setImagealt(GLuint texture, int width, int height);
    void clearImage();

    bool isImageLoaded() const;
    GLuint getImageTexture() const;
    int getImageWidth() const;
    int getImageHeight() const;

private:
    bool imageLoaded;
    GLuint imageTexture;
    int imageWidth;
    int imageHeight;
    GLuint altTexture;
    float zoomFactor;

    int flag;
};

#endif // CANVAS_WIDGET_HPP
