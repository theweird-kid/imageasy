#include "blur_effect.hpp"
#include <GL/gl.h>
#include <vector>
#include <cmath>

void checkGLError(const char* stmt, const char* fname, int line) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error " << err << " at " << fname << ":" << line << " - for " << stmt << std::endl;
    }
}

#define GL_CHECK(stmt) do { \
    stmt; \
    checkGLError(#stmt, __FILE__, __LINE__); \
} while (0)

BlurEffect::BlurEffect(const char* horizontalComputeShader, const char* verticalComputeShader)
    : horizontalShader(horizontalComputeShader), verticalShader(verticalComputeShader) {}

BlurEffect::~BlurEffect() {}

void printTextureData(GLuint texture, int width, int height) {
    std::vector<float> data(width * height * 4); // Assuming RGBA32F format
    glBindTexture(GL_TEXTURE_2D, texture);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, data.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    // Print the first few pixels for debugging
    for (int i = 0; i < std::min(10, width * height); ++i) {
        std::cout << "Pixel " << i << ": "
                  << data[i * 4 + 0] << ", "
                  << data[i * 4 + 1] << ", "
                  << data[i * 4 + 2] << ", "
                  << data[i * 4 + 3] << std::endl;
    }
}

void BlurEffect::apply(GLuint inputTexture, GLuint& outputTexture, int width, int height)
{
    // Print texture before blur
    // Debug: Print intput texture data
        std::cout << "Input Texture data before blur:" << std::endl;
        printTextureData(inputTexture, width, height);

    // Create an intermediate texture for the horizontal blur pass
        GLuint intermediateTexture;
        GL_CHECK(glGenTextures(1, &intermediateTexture));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, intermediateTexture));
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        // Apply the horizontal blur
        horizontalShader.useProgram();
        GL_CHECK(glBindImageTexture(0, inputTexture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F));
        GL_CHECK(glBindImageTexture(1, intermediateTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
        GL_CHECK(glDispatchCompute((GLuint)ceil(width / 16.0), (GLuint)ceil(height / 16.0), 1));
        GL_CHECK(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));

        // Debug: Print intermediate texture data
            std::cout << "Intermediate texture data after horizontal blur:" << std::endl;
            printTextureData(intermediateTexture, width, height);


        // Apply the vertical blur
        verticalShader.useProgram();
        GL_CHECK(glBindImageTexture(0, intermediateTexture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F));
        GL_CHECK(glBindImageTexture(1, outputTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
        GL_CHECK(glDispatchCompute((GLuint)ceil(width / 16.0), (GLuint)ceil(height / 16.0), 1));
        GL_CHECK(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));

        // Debug: Print output texture data
            std::cout << "Output texture data after vertical blur:" << std::endl;
            printTextureData(outputTexture, width, height);


        // Clean up
        GL_CHECK(glDeleteTextures(1, &intermediateTexture));
        glBindTexture(GL_TEXTURE_2D, 0);
}
