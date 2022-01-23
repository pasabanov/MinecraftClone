#include "headers/includes.h"

#include "engine/window/Window.h"
#include "game/world/VoxelWorld.h"

int main() {

    Window window ("Window");

    window.setView(
            std::unique_ptr<VoxelWorld>(
                    new VoxelWorld(
                            window.getWidth(),
                            window.getHeight(),
                            8, 2, 8)));


    glClearColor(0.6f,0.62f,0.65f,1);


    while(!window.isShouldClose()) {

        window.pollEvents();

        if (window.keyJustPressed(GLFW_KEY_ESCAPE)) {
            window.setShouldClose(true);
        }
        if (window.keyJustPressed(GLFW_KEY_TAB)) {
            window.toggleCursor();
        }

        window.refresh();
    }
}