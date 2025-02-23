#include "tool_canvas.hpp"
#include <imgui.h>
#include "../core/contrast_effect.hpp"

ToolCanvas::ToolCanvas(std::shared_ptr<Pipeline> pipeline)
    : pipeline(pipeline), selectedEffectIndex(-1), applyEffect(false), contrastFactor(1.0f)
{
    loadImageTool = std::make_unique<LoadImageTool>(pipeline);
}

void ToolCanvas::render()
{
    if (ImGui::Begin("Tools"))
    {
        loadImageTool->render();

        // Reset Image Button
        if (ImGui::Button("Reset Image"))
        {
            if (pipeline->isImageLoaded())
            {
                pipeline->resetImage();
            }
        }

        // Render buttons for each effect
        for (int i = 0; i < imageEffects.size(); ++i)
        {
            if (ImGui::Button(imageEffects[i].second.c_str()))
            {
                selectedEffectIndex = i;
                applyEffect = true;
            }

            // Render additional controls for specific effects
            if (imageEffects[i].second == "Contrast")
            {
                ImGui::SliderFloat("Contrast Factor", &contrastFactor, 0.0f, 3.0f);
            }
        }
    }
    ImGui::End();

    // Apply image effect if available and the button was clicked
    if (applyEffect && selectedEffectIndex >= 0 && pipeline->isImageLoaded())
    {
        auto& effect = imageEffects[selectedEffectIndex].first;
        if (imageEffects[selectedEffectIndex].second == "Contrast")
        {
            auto contrastEffect = std::dynamic_pointer_cast<ContrastEffect>(effect);
            if (contrastEffect)
            {
                contrastEffect->setContrastFactor(contrastFactor);
            }
        }

        pipeline->applyEffect([effect](GLuint inputTexture, GLuint outputTexture, int width, int height) {
            effect->apply(inputTexture, outputTexture, width, height);
        });

        // Reset the flag
        applyEffect = false;
    }
}

void ToolCanvas::addImageEffect(const std::shared_ptr<ImageEffect>& effect, const std::string& name)
{
    imageEffects.push_back({effect, name});
}
