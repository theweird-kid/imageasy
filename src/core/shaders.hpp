#ifndef SHADE_HPP
#define SHADE_HPP

#include <glad/glad.h>
#include <iostream>
#include <string>

class Shader{
public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void useProgram();

    // Utitlity functions
    std::string loadShader(const char* shaderPath);
    GLuint compileShader(const char* shaderPath, GLenum shaderType);

public:
    GLuint program;
};

#endif // SHADE_HPP
