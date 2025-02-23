#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <memory>
#include <vector>
#include "../backends/imgui_impl_glfw.h"
#include "../backends/imgui_impl_opengl3.h"

#include "../gui/gui.hpp"
#include "../core/shaders.hpp"

class Application {
public:
    Application() noexcept;
    ~Application();

    void run();
    void processInput();
    void render();

    void setWindow(GLFWwindow* window);
    GLFWwindow* getWindow();

    void GenerateBgShader();
    void renderBg();

private:
    // Resize window callback
    void framebufferSizeCallback(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    GLFWwindow* m_Window;
    std::unique_ptr<Gui> m_Gui;
    std::unique_ptr<Shader> m_backgroundShader;
    GLuint VAO, VBO;
    GLuint backgroundTexture;
};

#endif // !APPLICATION_HPP
