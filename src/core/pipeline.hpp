#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <glad/glad.h>
#include <memory>
#include <functional>

class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    void setImage(GLuint texture, int width, int height);
    void resetImage();
    void applyEffect(const std::function<void(GLuint, GLuint, int, int)>& effect);
    void clearImage();

    bool isImageLoaded() const;
    GLuint getOriginalImageTexture() const;
    GLuint getProcessedImageTexture() const;
    int getImageWidth() const;
    int getImageHeight() const;

private:
    bool imageLoaded;
    GLuint originalImageTexture;
    GLuint processedImageTexture;
    int imageWidth;
    int imageHeight;
};

#endif // PIPELINE_HPP
