#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H

#include "../headers/includes.h"
#include "../exception/MessageException.h"

class Window {
public:

    struct Key {
        bool pressed;
        uint frame;
    };

    inline static const int N_KEYS = 1024;
    inline static const int N_BUTTONS = 12;

    inline static std::map<GLFWwindow*,Window*> sWindows;

    GLFWwindow* mWindow;
    int mWidth, mHeight;
    std::string mTitle;

    std::vector<Key> mKeys; // keyboard
    std::vector<Key> mButtons; // mouse
    uint mCurrentFrame = 0;
    double mDeltaX = 0;
    double mDeltaY = 0;
    double mX = 0;
    double mY = 0;
    bool mCursorStarted = false;
    bool mCursorDisabled = false;

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

    inline static int DEFAULT_WIDTH = 1280;
    inline static int DEFAULT_HEIGHT = 720;

    class WindowCreationError : public MessageException {
    public:
        WindowCreationError(const std::string& message) : MessageException(message) {}
    };

    Window(const std::string& title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

    ~Window();

    bool isShouldClose() const;
    void setShouldClose(bool flag);

    void pollEvents();

    void swapBuffers();

    bool keyPressed(int keycode) const;
    bool keyJustPressed(int keycode) const;

    bool buttonPressed(int button) const;
    bool buttonJustPressed(int button) const;

    void disableCursor();
    void enableCursor();
    void toggleCursor();
    bool isCursorDisabled() const;

    int getWidth() const;
    int getHeight() const;

    const std::string& getTitle() const;
    void setTitle(const std::string& title);
};

#endif //MINECRAFT_WINDOW_H