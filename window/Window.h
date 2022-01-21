#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFWwindow; // pre-declaration

class Window {

    GLFWwindow* mWindow;

    static void error(const std::string& message);

public:

    Window(int width, int height, const std::string& title);

    bool isShouldClose();

    void swapBuffers();
};


#endif //MINECRAFT_WINDOW_H