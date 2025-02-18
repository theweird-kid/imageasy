#include "app.hpp"
#include <GLFW/glfw3.h>

Application::Application() noexcept {
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
    m_Window = glfwCreateWindow(800, 600, "Imageasy", NULL, NULL);
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
        exit(-1);
    }

    // Set the viewport
    glViewport(0, 0, 800, 600);

    // Setup GUI
    m_Gui = std::make_unique<Gui>(m_Window);
    auto imgLoader = std::make_shared<ImageLoaderWidget>();
    m_Gui->addWidget(imgLoader);
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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
