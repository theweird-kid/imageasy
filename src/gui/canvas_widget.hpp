#ifndef CANVAS_WIDGET_HPP
#define CANVAS_WIDGET_HPP

#include "../core/pipeline.hpp"

class CanvasWidget {
public:
    CanvasWidget(std::shared_ptr<Pipeline> pipeline);
    ~CanvasWidget();

    void render();
    void clearImage();

private:
    std::shared_ptr<Pipeline> pipeline;
    float zoomFactor;
};


#endif // CANVAS_WIDGET_HPP
