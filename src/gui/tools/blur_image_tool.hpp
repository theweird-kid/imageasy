#ifndef BLUR_IMAGE_TOOL_HPP
#define BLUR_IMAGE_TOOL_HPP

#include "../widget.hpp"
#include "../../core/shaders.hpp"
#include "../canvas_widget.hpp"

#include <GL/gl.h>
#include <vector>
#include <memory>
//#include <GL/gl.h>

class BlurImageTool : public Widget
{
public:
    BlurImageTool(std::shared_ptr<CanvasWidget> canvas);
    void render() override;
    void applyBlur(GLuint input, GLuint& output);
    void removeBlur();

private:
    void calculateKernel(int size);
    void renderQuad();

private:
    std::unique_ptr<Shader> m_BlurShader;
    std::shared_ptr<CanvasWidget> m_Canvas;

    GLuint fb;
    GLuint blurWorkingTexture;
    std::vector<float> m_Kernel;

    bool b_BlurApplied;
    bool b_BlurDirty;
};

#endif // BLUR_IMAGE_TOOL_HPP
