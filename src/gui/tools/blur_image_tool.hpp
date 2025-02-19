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
    void applyBlur();
    void removeBlur();

private:
    void calculateKernel(int size);

private:
    std::unique_ptr<Shader> m_Shader;
    std::shared_ptr<CanvasWidget> m_Canvas;

    float m_BlurSize;
    GLuint m_BluredTexture;
    GLuint m_FrameBuffer;
    std::vector<float> m_Kernel;
};

#endif // BLUR_IMAGE_TOOL_HPP
