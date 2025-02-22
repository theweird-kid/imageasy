#ifndef SHADE_HPP
#define SHADE_HPP

#include <glad/glad.h>
#include <iostream>
#include <string>

class Shader{
public:
    // Vertex and Fragment Shader Paths
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    // Compute Shader Path
    Shader(const char* computeShaderPath);
    Shader() = default;

    // Destructor
    ~Shader();

    void useProgram();

    // Utitlity functions
    std::string loadShader(const char* shaderPath);
    GLuint compileShader(const char* shaderPath, GLenum shaderType);

public:
    GLuint program;

    // Utility Functions
    void setFloat(const std::string &name, float value) const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
};

#endif // SHADE_HPP
