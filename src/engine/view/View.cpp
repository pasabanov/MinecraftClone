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