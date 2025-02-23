#ifndef CONTRAST_EFFECT_HPP
#define CONTRAST_EFFECT_HPP

#include "image_effect.hpp"
#include "shaders.hpp"

class ContrastEffect : public ImageEffect
{
public:
    ContrastEffect(const char* computeShader);
    void apply(GLuint inputTexture, GLuint& outputTexture, int width, int height) override;
    void setContrastFactor(float factor);
    ~ContrastEffect();

private:
    Shader shader;
    float contrastFactor;
};

#endif // CONTRAST_EFFECT_HPP
