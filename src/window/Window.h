#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H

#include "../headers/includes.h"

class Window {
public:

    struct Key {
        bool pressed;
        uint frame;
    };

    inline static const int N_KEYS = 1024;
    inline static const int N_BUTTONS = 12;

    inline static std::map<GLFWwindow*, Window*> sWindows;

    GLFWwindow* mWindow;
    int mWidth, mHeight;

    std::vector<Key> mKeys; // keyboard
    std::vector<Key> mButtons; // mouse
    uint mCurrentFrame = 0;
    double mDeltaX = 0;
    double mDeltaY = 0;
    double mX = 0;
    double mY = 0;
    bool mCursorDisabled = false;
    bool mCursorStarted = false;

    static void error(const std::string& message);

    static void cursorPositionCallback(GLFWwindow* glwindow, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* glwindow, int button, int action, int mode);
    static void keyboardKeyCallback(GLFWwindow* glwindow, int key, int scancode, int action, int mode);
    static void windowSizeCallback(GLFWwindow* glwindow, int width, int height);

    void cursorPositionCallback(double xpos, double ypos);
    void mouseButtonCallback(int button, int action, int mode);
    void keyboardKeyCallback(int keycode, int scancode, int action, int mode);
    void windowSizeCallback(int width, int height);

    void registerWindow() const;
    void unregisterWindow() const;

    void setCursorMode(int mode) const;

public:

    Window(int width, int height, const std::string& title);

    ~Window();

    bool isShouldClose() const;
    void setShouldClose(bool flag);

    void pollEvents();

    void swapBuffers();

    bool keyPressed(int keycode) const;
    bool keyJustPressed(int keycode) const;

    bool buttonPressed(int button) const;
    bool buttonJustPressed(int button) const;

    void toggleCursor();
    bool isCursorDisabled() const;

    int getWidth() const;
    int getHeight() const;
};

#endif //MINECRAFT_WINDOW_H