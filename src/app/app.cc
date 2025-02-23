#include "app.hpp"
#include "stb_image.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

Application::Application() noexcept {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    // Set GLFW context version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window and its OpenGL context
    m_Window = glfwCreateWindow(1920, 1080, "Imageasy", NULL, NULL);
    if (m_Window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_Window);

    // Load OpenGL functions using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        exit(-1);
    }

    // Query and print OpenGL renderer and vendor
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "Vendor: " << vendor << std::endl;


    // Set the viewport
    glViewport(0, 0, 1920, 1080);

    // Setup GUI
    m_Gui = std::make_unique<Gui>(m_Window);

    // Generate background shader
    GenerateBgShader();
}

Application::~Application() {
    // Clean up
    glfwDestroyWindow(this->m_Window);
    glfwTerminate();
}

void Application::run()
{
    while(!glfwWindowShouldClose(m_Window)) {
        // Process input
        processInput();

        // Start the ImGui frame
        m_Gui->newFrame();

        // Render here
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to #15273c
        glClear(GL_COLOR_BUFFER_BIT);

        renderBg();

        // Render GUI
        m_Gui->render();

        // Swap front and back buffers
        glfwSwapBuffers(m_Window);

        // Poll for and process events
        glfwPollEvents();

    }
}

void Application::processInput()
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_Window, true);
    }
}

void Application::GenerateBgShader()
{
    // Load background image
    int width, height, nrChannels;
    unsigned char* data = stbi_load("samples/bg.jpg", &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load background image" << std::endl;
        exit(-1);
    }

    // Create texture
    glGenTextures(1, &backgroundTexture);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Create shader program
    m_backgroundShader = std::make_unique<Shader>("src/core/shaders/vertex_bg.glsl", "src/core/shaders/fragment_bg.glsl");

    // Set up vertex data and buffers and configure vertex attributes
    float vertices[] = {
        // positions   // texture coords
        -1.0f,  1.0f,  0.0f, 0.0f,
        -1.0f, -1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 1.0f,

        -1.0f,  1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Application::renderBg()
{
    m_backgroundShader->useProgram();
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
