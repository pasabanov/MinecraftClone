#include <engine/window/Events.h>

Events::Events() {}

void Events::onNextFrame() {
    ++mCurrentFrame;
    mDeltaX = mDeltaY = 0;
}

bool Events::keyPressed(int keycode) const {
    try {
        return mKeys.at(keycode).pressed;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}

bool Events::keyJustPressed(int keycode) const {
    try {
        Key key = mKeys.at(keycode);
        return key.pressed && key.frame == mCurrentFrame;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}

void Events::onKeyPressed(int keycode) {
    Key& key = mKeys[keycode];
    key.pressed = true;
    key.frame = mCurrentFrame;
}

void Events::onKeyReleased(int keycode) {
    Key& key = mKeys[keycode];
    key.pressed = false;
    key.frame = mCurrentFrame;
}

void Events::onKeyboardKeyAction(int keycode, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        onKeyPressed(keycode);
    } else if (action == GLFW_RELEASE) {
        onKeyReleased(keycode);
    }
}

bool Events::buttonPressed(int button) const {
    try {
        return mButtons.at(button).pressed;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}

bool Events::buttonJustPressed(int button) const {
    try {
        Key key = mButtons.at(button);
        return key.pressed && key.frame == mCurrentFrame;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}

void Events::onButtonPressed(int button) {
    Key& key = mButtons[button];
    key.pressed = true;
    key.frame = mCurrentFrame;
}

void Events::onButtonReleased(int button) {
    Key& key = mButtons[button];
    key.pressed = false;
    key.frame = mCurrentFrame;
}

void Events::onMouseButtonAction(int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        onButtonPressed(button);
    } else if (action == GLFW_RELEASE) {
        onButtonReleased(button);
    }
}

double Events::getDeltaX() const {
    return mDeltaX;
}

double Events::getDeltaY() const {
    return mDeltaY;
}

double Events::getMouseX() const {
    return mX;
}

double Events::getMouseY() const {
    return mY;
}

void Events::onCursorPositionChanged(double xpos, double ypos) {
    if (mCursorStarted) {
        mDeltaX += xpos - mX;
        mDeltaY += ypos - mY;
    } else {
        mCursorStarted = true;
    }
    mX = xpos;
    mY = ypos;
}

void Events::disableCursor() {
    mCursorDisabled = true;
}

void Events::enableCursor() {
    mCursorDisabled = false;
}

void Events::toggleCursor() {
    mCursorDisabled = !mCursorDisabled;
}

bool Events::isCursorDisabled() const {
    return mCursorDisabled;
}