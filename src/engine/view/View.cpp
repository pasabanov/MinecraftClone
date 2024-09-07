#include <engine/view/View.h>

View::View(int width, int height) : mWidth(width), mHeight(height) {}

View::~View() {}

int View::getWidth() const {
	return mWidth;
}

void View::setWidth(int width) {
	mWidth = width;
}

int View::getHeight() const {
	return mHeight;
}

void View::setHeight(int height) {
	mHeight = height;
}

void View::refresh() {
	update();
	draw();
}