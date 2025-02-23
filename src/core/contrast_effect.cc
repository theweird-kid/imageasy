#include "contrast_effect.hpp"

ContrastEffect::ContrastEffect(const char* computeShader)
    : shader(computeShader), contrastFactor(1.0f)
{}

void ContrastEffect::apply(GLuint inputTexture, GLuint& outputTexture, int width, int height)
{
    // Bind the shader
    shader.useProgram();

    // Bind the input texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, inputTexture);
    shader.setInt("inputTexture", 0);

    // Set the contrast factor
    shader.setFloat("contrastFactor", contrastFactor);

    // Bind the output texture
    glBindImageTexture(1, outputTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    // Dispatch the compute shader
    glDispatchCompute((GLuint)width, (GLuint)height, 1);

    // Ensure all writes to the image are finished
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void ContrastEffect::setContrastFactor(float factor)
{
    contrastFactor = factor;
}

ContrastEffect::~ContrastEffect() {}
