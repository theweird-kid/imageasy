#ifndef IMAGE_EFFECT_HPP
#define IMAGE_EFFECT_HPP

#include <glad/glad.h>

// Image Effect Interface
class ImageEffect {
public:
    virtual void apply(GLuint inputTexture, GLuint& outputTexture, int width, int height) = 0;
    virtual ~ImageEffect() = default;
};

#endif // IMAGE_EFFECT_HPP
