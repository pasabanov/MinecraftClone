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