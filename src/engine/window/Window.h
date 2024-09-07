#pragma once

/*
 * MinecraftClone
 * Copyright (C) © 2022  Petr Alexandrovich Sabanov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <headers/includes.h>

#include <engine/exception/MessageException.h>
#include <engine/view/View.h>
#include <engine/time/Clock.h>

class Window {

	inline static std::map<GLFWwindow*,Window*> sWindows;

	GLFWwindow* mWindow;
	int mWidth, mHeight;
	std::string mTitle;

	Events mEvents;

	Clock mClock;

	std::unique_ptr<View> mView;

	static void cursorPositionCallback(GLFWwindow* glwindow, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* glwindow, int button, int action, int mode);
	static void keyboardKeyCallback(GLFWwindow* glwindow, int key, int scancode, int action, int mode);
	static void windowSizeCallback(GLFWwindow* glwindow, int width, int height);

	void onCursorPositionChanged(double xpos, double ypos);
	void onMouseButtonAction(int button, int action, int mode);
	void onKeyboardKeyAction(int keycode, int scancode, int action, int mode);
	void onWindowSizeChanged(int width, int height);

	void registerWindow() const;
	void unregisterWindow() const;

	void setCursorMode(int mode) const;

	void swapBuffers() const;

public:

	inline static int DEFAULT_WIDTH = 1280;
	inline static int DEFAULT_HEIGHT = 720;

	class WindowCreationException : public MessageException {
	public:
		WindowCreationException(const std::string& message) : MessageException(message) {}
	};

	Window(const std::string& title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

	~Window();

	std::unique_ptr<View>& getView();
	const std::unique_ptr<View>& getView() const;
	void setView(std::unique_ptr<View>&& view);

	bool isShouldClose() const;
	void setShouldClose(bool flag);

	void pollEvents();

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

	void requestFocus() const;

	void fillColor(float red = 1, float green = 1, float blue = 1, float alpha = 1);

	void refresh();
};