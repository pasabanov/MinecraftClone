#include "Window.h"



void Window::error(const std::string& message) {
    std::cerr << message << '\n';
    glfwTerminate();
    exit(1);
}



Window::Window(int width, int height, const std::string& title) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    mWindow = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
    if (mWindow == nullptr)
        error("Failed to create window");
    glfwMakeContextCurrent(mWindow);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        error("Failed to initialize GLEW");

    glViewport(0, 0, width, height);
}



bool Window::isShouldClose() {
    return glfwWindowShouldClose(mWindow);
}



void Window::swapBuffers() {
    glfwSwapBuffers(mWindow);
}