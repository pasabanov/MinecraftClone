#ifndef MINECRAFT_EVENTS_H
#define MINECRAFT_EVENTS_H

#include "../../headers/includes.h"

#include "Key.h"

class Events {

    inline static const int N_KEYS = 1024;
    inline static const int N_BUTTONS = 12;

    std::vector<Key> mKeys { N_KEYS }; // keyboard
    std::vector<Key> mButtons { N_BUTTONS }; // mouse
    uint mCurrentFrame = 0;
    double mDeltaX = 0;
    double mDeltaY = 0;
    double mX = 0;
    double mY = 0;
    bool mCursorStarted = false;
    bool mCursorDisabled = false;

public:

    Events();

    void onNextFrame();

    bool keyPressed(int keycode) const;
    bool keyJustPressed(int keycode) const;
    void onKeyPressed(int keycode);
    void onKeyReleased(int keycode);
    void onKeyboardKeyAction(int keycode, int scancode, int action, int mode);

    bool buttonPressed(int button) const;
    bool buttonJustPressed(int button) const;
    void onButtonPressed(int button);
    void onButtonReleased(int button);
    void onMouseButtonAction(int button, int action, int mode);

    double getDeltaX() const;
    double getDeltaY() const;
    double getMouseX() const;
    double getMouseY() const;
    void onCursorPositionChanged(double xpos, double ypos);

    void disableCursor();
    void enableCursor();
    void toggleCursor();
    bool isCursorDisabled() const;
};

#endif //MINECRAFT_EVENTS_H