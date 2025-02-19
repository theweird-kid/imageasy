#include "shaders.hpp"
#include <GL/gl.h>
#include <sstream>
#include <fstream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    : program(0)
{
    // Load and compile shaders
    GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    // Link shaders
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Failed to link shader program: " << infoLog << std::endl;
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::compileShader(const char* shaderPath, GLenum shaderType)
{
    // Load shader source code
    std::string shaderSource = loadShader(shaderPath);
    const char* shaderCode = shaderSource.c_str();

    // Compile shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Failed to compile shader: " << infoLog << std::endl;
    }

    return shader;
}

std::string Shader::loadShader(const char* shaderPath)
{
    std::string shaderCode;
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open file
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;

        // Read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();

        // Close file
        shaderFile.close();

        // Convert stream into string
        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Failed to read shader file: " << shaderPath << std::endl;
    }

    return shaderCode;
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::useProgram()
{
    glUseProgram(program);
}
