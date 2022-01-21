#include "Window.h"



void Window::error(const std::string& message) {
    std::cerr << message << '\n';
    glfwTerminate();
    exit(1);
}



void Window::cursorPositionCallback(GLFWwindow* glwindow, double xpos, double ypos) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->cursorPositionCallback(xpos, ypos);
}



void Window::mouseButtonCallback(GLFWwindow* glwindow, int button, int action, int mode) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->mouseButtonCallback(button, action, mode);
}



void Window::keyboardKeyCallback(GLFWwindow* glwindow, int key, int scancode, int action, int mode) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->keyboardKeyCallback(key, scancode, action, mode);
}



void Window::windowSizeCallback(GLFWwindow* glwindow, int width, int height) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->windowSizeCallback(width, height);
}



void Window::cursorPositionCallback(double xpos, double ypos) {
    if (mCursorStarted) {
        mDeltaX += xpos - mX;
        mDeltaY += ypos - mY;
    } else {
        mCursorStarted = true;
    }
    mX = xpos;
    mY = ypos;
}



void Window::mouseButtonCallback(int button, int action, int mode) {
    Key& key = mButtons[button];
    if (action == GLFW_PRESS) {
        key.pressed = true;
        key.frame = mCurrentFrame;
    } else if (action == GLFW_RELEASE) {
        key.pressed = false;
        key.frame = mCurrentFrame;
    }
}



void Window::keyboardKeyCallback(int keycode, int scancode, int action, int mode) {
    Key& key = mKeys[keycode];
    if (action == GLFW_PRESS) {
        key.pressed = true;
        key.frame = mCurrentFrame;
    } else if (action == GLFW_RELEASE) {
        key.pressed = false;
        key.frame = mCurrentFrame;
    }
}



void Window::windowSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
    mWidth = width;
    mHeight = height;
}



void Window::registerWindow() const {
    sWindows[mWindow] = (Window*) this;
}



void Window::unregisterWindow() const {
    sWindows.erase(mWindow);
}



void Window::setCursorMode(int mode) const {
    glfwSetInputMode(mWindow, GLFW_CURSOR, mode);
}



Window::Window(int width, int height, const std::string& title)
: mWidth(width), mHeight(height), mKeys(N_KEYS), mButtons(N_BUTTONS) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, true);

    mWindow = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
    if (mWindow == nullptr)
        error("Failed to create window");
    glfwMakeContextCurrent(mWindow);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        error("Failed to initialize GLEW");

    glViewport(0, 0, width, height);

    glfwSetCursorPosCallback(mWindow, cursorPositionCallback);
    glfwSetMouseButtonCallback(mWindow, mouseButtonCallback);
    glfwSetKeyCallback(mWindow, keyboardKeyCallback);
    glfwSetWindowSizeCallback(mWindow, windowSizeCallback);

    registerWindow();
}



Window::~Window() {
    unregisterWindow();
    glfwDestroyWindow(mWindow);
}



bool Window::isShouldClose() const {
    return glfwWindowShouldClose(mWindow);
}



void Window::setShouldClose(bool flag) {
    glfwSetWindowShouldClose(mWindow, flag);
}



void Window::pollEvents() {
    ++mCurrentFrame;
    mDeltaX = mDeltaY = 0;
    glfwPollEvents();
}



void Window::swapBuffers() {
    glfwSwapBuffers(mWindow);
}



bool Window::keyPressed(int keycode) const {
    try {
        return mKeys.at(keycode).pressed;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}



bool Window::keyJustPressed(int keycode) const {
    try {
        Key key = mKeys.at(keycode);
        return key.pressed && key.frame == mCurrentFrame;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}



bool Window::buttonPressed(int button) const {
    try {
        return mButtons.at(button).pressed;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}



bool Window::buttonJustPressed(int button) const {
    try {
        Key key = mButtons.at(button);
        return key.pressed && key.frame == mCurrentFrame;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}



void Window::toggleCursor() {
    mCursorDisabled = !mCursorDisabled;
    setCursorMode(mCursorDisabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}



bool Window::isCursorDisabled() const {
    return mCursorDisabled;
}



int Window::getWidth() const {
    return mWidth;
}



int Window::getHeight() const {
    return mHeight;
}