#include "View.h"



View::View(int width, int height) : mViewWidth(width), mViewHeight(height) {}



View::~View() {}



int View::getViewWidth() const {
    return mViewWidth;
}

void View::setViewWidth(int width) {
    mViewWidth = width;
}

int View::getViewHeight() const {
    return mViewHeight;
}

void View::setViewHeight(int height) {
    mViewHeight = height;
}



void View::refresh() {
    update();
    draw();
}