#include "blur_image_tool.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <imgui.h>
#include <iostream>
#include <stb_image.h>

BlurImageTool::BlurImageTool(std::shared_ptr<CanvasWidget> canvas)
    : m_Canvas(canvas), blurWorkingTexture(0) {
  // Init the shaders
  m_BlurShader =
      std::make_unique<Shader>("src/core/shaders/blur/blur_vertex.glsl",
                               "src/core/shaders/blur/blur_fragment.glsl");
  calculateKernel(25);
  glGenFramebuffers(1, &fb);
}

void BlurImageTool::render() {
  if (ImGui::Button("Apply Blur")) {
    GLuint output;
    applyBlur(m_Canvas->getImageTexture(), output);
    m_Canvas->setImage(output, m_Canvas->getImageWidth(),
                       m_Canvas->getImageHeight());
  }
  ImGui::SameLine();
  if (ImGui::Button("Remove Blur")) {
    m_Canvas->clearImage();
  }
}

void BlurImageTool::applyBlur(GLuint input, GLuint &output) {
  int width = m_Canvas->getImageWidth();
  int height = m_Canvas->getImageHeight();

  // Create a texture to store the output
  glGenTextures(1, &output);
  glBindTexture(GL_TEXTURE_2D, output);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Bind the framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, fb);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         output, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Framebuffer not complete!" << std::endl;
    return;
  }

  // Use the blur shader
  m_BlurShader->useProgram();
  glUniform1fv(glGetUniformLocation(m_BlurShader->program, "weight"),
               m_Kernel.size(), m_Kernel.data());
  glUniform1i(glGetUniformLocation(m_BlurShader->program, "kernelSize"),
              m_Kernel.size());

  // Bind the input texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, input);
  glUniform1i(glGetUniformLocation(m_BlurShader->program, "image"), 0);

  // Horizontal pass
  glUniform1i(glGetUniformLocation(m_BlurShader->program, "horizontal"),
              GL_TRUE);
  renderQuad();

  // Vertical pass
  glUniform1i(glGetUniformLocation(m_BlurShader->program, "horizontal"),
              GL_FALSE);
  renderQuad();

  // Unbind the framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, m_Canvas->getImageWidth(), m_Canvas->getImageHeight());
}

void BlurImageTool::calculateKernel(int size) {
  m_Kernel.clear();

  double sigma = 1;
  std::vector<std::vector<float>> kernel(size, std::vector<float>(size, 0));
  float mean = int(size / 2);
  float sum = 0.0;

  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      kernel[x][y] = (float)sqrt(exp(-0.5 * (pow((x - mean) / sigma, 2.0)) +
                                     pow((y - mean) / sigma, 2.0))) /
                     (2 * glm::pi<double>() * sigma * sigma);
      // Accumulate the kernel values
      sum += kernel[x][y];
    }
  }

  // Normalize the kernel
  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      kernel[x][y] /= sum;
    }
  }

  for (int x = 0; x < size; x++) {
    float result = 0;
    for (int y = 0; y < size; y++) {
      result += kernel[x][y];
    }
    if (x >= (int(size / 2))) {
      m_Kernel.push_back(result);
    }
  }
}

void BlurImageTool::renderQuad() {
  static GLuint quadVAO = 0;
  static GLuint quadVBO;

  if (quadVAO == 0) {
    float quadVertices[] = {// positions        // texture coords
                            -1.0f, 1.0f, 0.0f, 0.0f,  1.0f, -1.0f, -1.0f, 0.0f,
                            0.0f,  0.0f, 1.0f, -1.0f, 0.0f, 1.0f,  0.0f,

                            -1.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  -1.0f, 0.0f,
                            1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,  1.0f};

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
  }

  glBindVertexArray(quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
