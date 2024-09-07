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

#include <engine/window/Window.h>
#include <game/world/VoxelWorld.h>
#include <app/Application.h>

int main() {

	Window window (Application::APP_NAME);

	window.setView(
		std::make_unique<VoxelWorld>(
			window.getWidth(),
			window.getHeight(),
			2, 1, 2
		)
	);

	window.fillColor(0.6, 0.62, 0.65);

	while(!window.isShouldClose()) {

		window.pollEvents();

		if (window.keyJustPressed(GLFW_KEY_ESCAPE)) {
			window.setShouldClose(true);
		}
		if (window.keyJustPressed(GLFW_KEY_F2)) {
			static_cast<const VoxelWorld&>(*window.getView()).save("world.bin");
		}
		if (window.keyJustPressed(GLFW_KEY_F3)) {
			static_cast<VoxelWorld&>(*window.getView()).load("world.bin");
		}
		if (window.keyJustPressed(GLFW_KEY_TAB)) {
			window.toggleCursor();
		}

		window.refresh();
	}
}