#ifndef LOAD_IMAGE_TOOL_HPP
#define LOAD_IMAGE_TOOL_HPP

#include <memory>
#include "../../core/pipeline.hpp"

class LoadImageTool {
public:
    LoadImageTool(std::shared_ptr<Pipeline> pipeline);
    void render();

private:
    void loadImage();
    void removeImage();

    std::shared_ptr<Pipeline> pipeline;
};

#endif // LOAD_IMAGE_TOOL_HPP
