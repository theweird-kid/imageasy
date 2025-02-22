#include "tool_canvas.hpp"
#include <imgui.h>
#include <tinyfiledialogs.h>
#include <stb_image.h>
#include "../core/blur_effect.hpp"
#include <iostream>

void checkGLError1(const char* stmt, const char* fname, int line) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error " << err << " at " << fname << ":" << line << " - for " << stmt << std::endl;
    }
}

#define GL_CHECK1(stmt) do { \
    stmt; \
    checkGLError1(#stmt, __FILE__, __LINE__); \
} while (0)

ToolCanvas::ToolCanvas(std::shared_ptr<CanvasWidget> canvas)
    : canvas(canvas)
{
    imageEffect = std::make_shared<BlurEffect>("src/core/shaders/blur_horizontal.glsl", "src/core/shaders/blur_vertical.glsl");
}

void ToolCanvas::render() {
    if (ImGui::Begin("Tools")) {
        for (auto& tool : tools) {
            tool->render();
        }
    }
    // Add a button to apply the blur effect
    if (ImGui::Button("Apply Blur")) {
        applyBlur = true;
    }
    ImGui::End();

    // Apply image effect if available and the button was clicked
        if (applyBlur && imageEffect && canvas->isImageLoaded()) {
            GLuint inputTexture = canvas->getImageTexture();
            int width = canvas->getImageWidth();
            int height = canvas->getImageHeight();

            // Create an output texture
                    GLuint outputTexture;
                    GL_CHECK1(glGenTextures(1, &outputTexture));
                    GL_CHECK1(glBindTexture(GL_TEXTURE_2D, outputTexture));
                    GL_CHECK1(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr));
                    GL_CHECK1(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
                    GL_CHECK1(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

                    // Apply the image effect
                    imageEffect->apply(inputTexture, outputTexture, width, height);

                    // Update the canvas with the output texture
                    canvas->setImagealt(outputTexture, width, height);

                    // Clean up
                    //GL_CHECK1(glDeleteTextures(1, &outputTexture));

                    // Reset the flag
                    applyBlur = false;

        }
}

void ToolCanvas::addTool(std::shared_ptr<Widget> tool) {
    tools.push_back(tool);
}
