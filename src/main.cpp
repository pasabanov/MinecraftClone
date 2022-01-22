#include "headers/includes.h"

#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "graphics/VoxelsRenderer.h"
#include "voxel/Chunk.h"
#include "camera/Camera.h"
#include "time/Clock.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() {

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, "Window");

    Shader shader;

    try {
        shader.load("../res/shaders/main.glslv", "../res/shaders/main.glslf");
    } catch (const Shader::ShaderCreationException& exception) {
        std::cerr << "failed to load shader\n";
        return 1;
    }

    Texture texture;

    try {
        texture.load("../res/images/blocks.png");
    } catch (const Texture::TextureCreationException& exception) {
        std::cerr << "failed to load texture\n";
        return 1;
    }

    VoxelsRenderer renderer (1024 * 1024);

    Chunk chunk;

    Mesh mesh = renderer.render(chunk);

    glClearColor(0.6f,0.62f,0.65f,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera (&window, glm::vec3(0, 0, 1), glm::radians(70.0f));

    glm::mat4 model(1.0f);

    Clock clock;

    float camX = 0, camY = 0;

    double speed = 0.005;
    float sensitivityX = 2, sensitivityY = 2;

    while(!window.isShouldClose()) {

        long elapsedTime = clock.elapsedTimeMillis();

        double curSpeed = speed;

        window.pollEvents();
        if (window.keyJustPressed(GLFW_KEY_ESCAPE)) {
            window.setShouldClose(true);
        }
        if (window.keyJustPressed(GLFW_KEY_TAB)) {
            window.toggleCursor();
        }
        if (window.keyPressed(GLFW_KEY_LEFT_SHIFT)) {
            curSpeed *= 3;
        }
        if (window.keyPressed(GLFW_KEY_W)) {
            camera.moveRelative(glm::vec3(-elapsedTime * curSpeed, 0, 0));
        }
        if (window.keyPressed(GLFW_KEY_S)) {
            camera.moveRelative(glm::vec3(elapsedTime * curSpeed, 0, 0));
        }
        if (window.keyPressed(GLFW_KEY_A)) {
            camera.moveRelative(glm::vec3(0, -elapsedTime * curSpeed, 0));
        }
        if (window.keyPressed(GLFW_KEY_D)) {
            camera.moveRelative(glm::vec3(0, elapsedTime * curSpeed, 0));
        }
        if (window.keyPressed(GLFW_KEY_SPACE)) {
            camera.moveDirect(glm::vec3(0, -elapsedTime * curSpeed, 0));
        }
        if (window.keyPressed(GLFW_KEY_LEFT_CONTROL)) {
            camera.moveDirect(glm::vec3(0, elapsedTime * curSpeed, 0));
        }
        if (window.mCursorDisabled) {
            camX += sensitivityX * -window.mDeltaX / window.getWidth();
            camY += sensitivityY * -window.mDeltaY / window.getHeight();
            if (camY < -glm::radians(89.0f))
                camY = -glm::radians(89.0f);
            else if (camY > glm::radians(89.0f))
                camY = glm::radians(89.0f);
            camera.setRotation(glm::mat4(1));
            camera.rotate(glm::vec3(camY, camX, 0));
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.uniformMatrix("model", model);
        shader.uniformMatrix("projview", camera.getProjection() * camera.getView());
        texture.bind();
        mesh.draw(GL_TRIANGLES);

        window.swapBuffers();
    }
}