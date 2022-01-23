#ifndef MINECRAFT_VIEW_H
#define MINECRAFT_VIEW_H

#include "../../headers/includes.h"

#include "../window/Events.h"

class View {

    int mViewWidth, mViewHeight;

public:

    View(int width = 0, int height = 0);

    virtual ~View();

    virtual int getViewWidth() const;
    virtual void setViewWidth(int width);
    virtual int getViewHeight() const;
    virtual void setViewHeight(int height);

    virtual void onCursorPositionChanged(double xpos, double ypos, double deltaX, double deltaY) {
    }
    virtual void onMouseButtonAction(int button, int action, int mode) {
    }
    virtual void onKeyboardKeyAction(int keycode, int scancode, int action, int mode) {
    }
    virtual void onViewSizeChanged(int width, int height) {
    }

    virtual void applyEvents(const Events& events, float elapsedTime) {
    }

    virtual void update() = 0;

    virtual void draw() const = 0;

    virtual void refresh();
};

#endif //MINECRAFT_VIEW_H