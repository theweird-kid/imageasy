#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "../backends/imgui_impl_glfw.h"
#include "../backends/imgui_impl_opengl3.h"

class Application {
public:
    Application() noexcept
    {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(-1);
        }

        // Set GLFW context version and profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window and its OpenGL context
        window = glfwCreateWindow(800, 600, "Imageasy", NULL, NULL);
        if(window == nullptr) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Load OpenGL functions using glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }

        // Set the viewport
        glViewport(0, 0, 800, 600);

        // Setup ImGui
        setupImGui();
    }

    // Destructor
    ~Application()
    {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    // Run
    void run()
    {
        while (!glfwWindowShouldClose(window)) {
            // Process input
            processInput();

            // Render here
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    void processInput()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    void render()
    {

    }

    void setWindow(GLFWwindow* window);
    GLFWwindow* getWindow();

private:
    // Resize window callback
    void framebufferSizeCallback(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void setupImGui()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(this->window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    GLFWwindow* window;
};

#endif // !APPLICATION_HPP
