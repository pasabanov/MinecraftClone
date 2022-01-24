#include "Window.h"



void Window::cursorPositionCallback(GLFWwindow* glwindow, double xpos, double ypos) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->onCursorPositionChanged(xpos, ypos);
}

void Window::mouseButtonCallback(GLFWwindow* glwindow, int button, int action, int mode) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->onMouseButtonAction(button, action, mode);
}

void Window::keyboardKeyCallback(GLFWwindow* glwindow, int key, int scancode, int action, int mode) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->onKeyboardKeyAction(key, scancode, action, mode);
}

void Window::windowSizeCallback(GLFWwindow* glwindow, int width, int height) {
    Window* window = sWindows[glwindow];
    if (window != nullptr)
        window->onWindowSizeChanged(width, height);
}



void Window::onCursorPositionChanged(double xpos, double ypos) {

    mEvents.onCursorPositionChanged(xpos, ypos);

    if (mView != nullptr)
        mView->onCursorPositionChanged(xpos, ypos, mEvents.getDeltaX(), mEvents.getDeltaY());
}

void Window::onMouseButtonAction(int button, int action, int mode) {

    mEvents.onMouseButtonAction(button, action, mode);

    if (mView != nullptr)
        mView->onMouseButtonAction(button, action, mode);
}

void Window::onKeyboardKeyAction(int keycode, int scancode, int action, int mode) {

    mEvents.onKeyboardKeyAction(keycode, scancode, action, mode);

    if (mView != nullptr)
        mView->onKeyboardKeyAction(keycode, scancode, action, mode);
}

void Window::onWindowSizeChanged(int width, int height) {

    glViewport(0, 0, width, height);
    mWidth = width;
    mHeight = height;

    if (mView != nullptr)
        mView->onViewSizeChanged(width, height);
}



void Window::registerWindow() const {
    sWindows[mWindow] = const_cast<Window*>(this);
}

void Window::unregisterWindow() const {
    sWindows.erase(mWindow);
}



void Window::setCursorMode(int mode) const {
    glfwSetInputMode(mWindow, GLFW_CURSOR, mode);
}



void Window::swapBuffers() const {
    glfwSwapBuffers(mWindow);
}



Window::Window(const std::string& title, int width, int height)
: mTitle(title), mWidth(width), mHeight(height) {

    if (glfwInit() != GLFW_TRUE)
        throw WindowCreationException("Failed to init GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, true);

    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (mWindow == nullptr)
        throw WindowCreationException("Failed to create window");

    glfwMakeContextCurrent(mWindow);

    glewExperimental = true;

    if (glewInit() != GLEW_OK)
        throw WindowCreationException("Failed to initialize GLEW");

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



std::unique_ptr<View>& Window::getView() {
    return mView;
}

const std::unique_ptr<View>& Window::getView() const {
    return mView;
}

void Window::setView(std::unique_ptr<View>&& view) {
    mView = std::move(view);
}



bool Window::isShouldClose() const {
    return glfwWindowShouldClose(mWindow);
}

void Window::setShouldClose(bool flag) {
    glfwSetWindowShouldClose(mWindow, flag);
}



void Window::pollEvents() {
    mEvents.onNextFrame();
    glfwPollEvents();
    if (mView != nullptr)
        mView->applyEvents(mEvents, mClock.elapsedTimeMillis());
}



bool Window::keyPressed(int keycode) const {
    return mEvents.keyPressed(keycode);
}

bool Window::keyJustPressed(int keycode) const {
    return mEvents.keyJustPressed(keycode);
}



bool Window::buttonPressed(int button) const {
    return mEvents.buttonPressed(button);
}

bool Window::buttonJustPressed(int button) const {
    return mEvents.buttonJustPressed(button);
}



void Window::disableCursor() {
    mEvents.disableCursor();
    setCursorMode(GLFW_CURSOR_DISABLED);
}

void Window::enableCursor() {
    mEvents.enableCursor();
    setCursorMode(GLFW_CURSOR_NORMAL);
}

void Window::toggleCursor() {
    mEvents.toggleCursor();
    setCursorMode(mEvents.isCursorDisabled() ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool Window::isCursorDisabled() const {
    return mEvents.isCursorDisabled();
}



int Window::getWidth() const {
    return mWidth;
}

int Window::getHeight() const {
    return mHeight;
}



const std::string& Window::getTitle() const {
    return mTitle;
}

void Window::setTitle(const std::string& title) {
    mTitle = title;
    glfwSetWindowTitle(mWindow, title.c_str());
}



void Window::requestFocus() const {
    glfwMakeContextCurrent(mWindow);
}



void Window::refresh() {
    requestFocus();
    if (mView != nullptr)
        mView->refresh();
    swapBuffers();
}