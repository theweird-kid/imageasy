#ifndef LOAD_IMAGE_TOOL_HPP
#define LOAD_IMAGE_TOOL_HPP

#include "widget.hpp"
#include "canvas_widget.hpp"
#include <memory>

class LoadImageTool : public Widget {
public:
    LoadImageTool(std::shared_ptr<CanvasWidget> canvas);
    void render() override;

private:
    void loadImage();
    void removeImage();

    std::shared_ptr<CanvasWidget> canvas;
};

#endif // LOAD_IMAGE_TOOL_HPP
