#include "blur_image_tool.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <imgui.h>
#include <stb_image.h>
#include <iostream>

BlurImageTool::BlurImageTool(std::shared_ptr<CanvasWidget> canvas)
 : m_BlurSize(1.0f), m_Canvas(canvas)
{
    // Init the shader
    m_Shader = std::make_unique<Shader>("src/core/shaders/blur/blur_vertex.glsl", "src/core/shaders/blur/blur_fragment.glsl");
    calculateKernel(7);
}

void BlurImageTool::render() {
    if (ImGui::Begin("Blur Image Tool")) {
        ImGui::SliderFloat("Blur Size", &m_BlurSize, 0.0f, 10.0f);

        if (ImGui::Button("Apply Blur")) {
            if (m_Canvas->isImageLoaded()) {
                applyBlur();
            } else {
                std::cerr << "No image loaded to apply blur." << std::endl;
            }
        }
    }
    ImGui::End();
}

void BlurImageTool::applyBlur() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Delete previous textures and framebuffers if they exist
    if (m_BluredTexture) {
        glDeleteTextures(1, &m_BluredTexture);
    }
    if (m_FrameBuffer) {
        glDeleteFramebuffers(1, &m_FrameBuffer);
    }

    // Generate and bind the framebuffer
    glGenFramebuffers(1, &m_FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

    // Generate and bind the texture to store the blurred image
    glGenTextures(1, &m_BluredTexture);
    glBindTexture(GL_TEXTURE_2D, m_BluredTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Canvas->getImageWidth(), m_Canvas->getImageHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BluredTexture, 0);
}

void BlurImageTool::calculateKernel(int size) {
    m_Kernel.clear();

    double sigma = 1;
    std::vector<std::vector<float>> kernel(size, std::vector<float>(size, 0));
    float mean = int(size/2);
    float sum = 0.0;

    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            kernel[x][y] = (float)sqrt(exp(-0.5*(pow( (x-mean)/sigma , 2.0)) + pow( (y-mean)/sigma , 2.0))) / (2 * glm::pi<double>() * sigma * sigma);
            // Accumulate the kernel values
            sum += kernel[x][y];
        }
    }

    // Normalize the kernel
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            kernel[x][y] /= sum;
        }
    }

    for(int x = 0; x < size; x++) {
        float result = 0;
        for(int y = 0; y < size; y++) {
            result += kernel[x][y];
        }
        if(x >= (int(size/2)) ) {
            m_Kernel.push_back(result);
        }
    }
}
