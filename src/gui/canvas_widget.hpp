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
    void clearImage();

private:
    bool imageLoaded;
    GLuint imageTexture;
    int imageWidth;
    int imageHeight;
};

#endif // CANVAS_WIDGET_HPP
