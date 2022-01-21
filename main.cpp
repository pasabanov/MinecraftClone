#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window/Window.h"

int WIDTH = 1280;
int HEIGHT = 720;

int main() {

    std::cout << "Hello, World!\n";

    Window window (1280, 720, "Window");

    while(!window.isShouldClose()) {
        glfwPollEvents();
        window.swapBuffers();

    }
}