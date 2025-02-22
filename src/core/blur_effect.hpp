#ifndef BLUR_EFFECT_HPP
#define BLUR_EFFECT_HPP

#include "image_effect.hpp"
#include "shaders.hpp"

class BlurEffect : public ImageEffect
{
public:
    BlurEffect(const char* horizontalComputeShader, const char* verticalComputeShader);
    void apply(GLuint inputTexture, GLuint& outputTexture, int width, int height) override;
    ~BlurEffect();

private:
    Shader horizontalShader, verticalShader;
};

#endif // BLUR_EFFECT_HPP
