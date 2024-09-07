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

#include <engine/window/Events.h>

class View {

	int mWidth, mHeight;

public:

	View(int width = 0, int height = 0);

	virtual ~View();

	virtual int getWidth() const;
	virtual void setWidth(int width);
	virtual int getHeight() const;
	virtual void setHeight(int height);

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