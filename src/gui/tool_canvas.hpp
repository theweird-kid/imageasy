#ifndef TOOL_CANVAS_HPP
#define TOOL_CANVAS_HPP

#include <vector>
#include <memory>
#include "widget.hpp"
#include "canvas_widget.hpp"

class ToolCanvas {
public:
    ToolCanvas(std::shared_ptr<CanvasWidget> canvas);
    void render();
    void addTool(std::shared_ptr<Widget> tool);

private:
    std::vector<std::shared_ptr<Widget>> tools;
    std::shared_ptr<CanvasWidget> canvas;
};

#endif // TOOL_CANVAS_HPP
