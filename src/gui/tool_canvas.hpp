#ifndef TOOL_CANVAS_HPP
#define TOOL_CANVAS_HPP

#include <memory>
#include <vector>
#include <string>
#include "../core/image_effect.hpp"
#include "../core/pipeline.hpp"
#include "./tools/load_image_tool.hpp"

class ToolCanvas {
public:
    ToolCanvas(std::shared_ptr<Pipeline> pipeline);
    void render();
    void addImageEffect(const std::shared_ptr<ImageEffect>& effect, const std::string& name);

private:
    std::shared_ptr<Pipeline> pipeline;
    std::vector<std::pair<std::shared_ptr<ImageEffect>, std::string>> imageEffects;
    std::unique_ptr<LoadImageTool> loadImageTool;
    int selectedEffectIndex;
    bool applyEffect;
    float contrastFactor; // Add a member variable for the contrast factor
};

#endif // TOOL_CANVAS_HPP
