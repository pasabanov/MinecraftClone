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

#include <engine/window/Key.h>

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