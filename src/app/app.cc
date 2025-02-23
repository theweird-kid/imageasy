#include "app.hpp"
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
