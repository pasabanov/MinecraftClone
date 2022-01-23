#include "headers/includes.h"

#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture2D.h"
#include "graphics/VoxelsRenderer.h"
#include "voxel/ChunkHeap.h"
#include "camera/Camera.h"
#include "time/Clock.h"

const float crosshair_vertices[] = {
        -0.01, -0.01,
        0.01, 0.01,

        -0.01, 0.01,
        0.01, -0.01
};

const int crosshair_attrs[] = {
        2, 0
};

int main() {

    Window window ("Window");

    Shader shader;

    try {
        shader.load("../res/shaders/main.glslv", "../res/shaders/main.glslf");
    } catch (const Shader::ShaderCreationException& exception) {
        std::cerr << "failed to load shader\n";
        return 1;
    }

    Shader crosshairShader;

    try {
        crosshairShader.load("../res/shaders/crosshair.glslv", "../res/shaders/crosshair.glslf");
    } catch (const Shader::ShaderCreationException& exception) {
        std::cerr << "failed to load crosshairShader\n";
        return 1;
    }

    Texture2D texture;

    try {
        texture.load("../res/images/blocks.png");
    } catch (const Texture2D::TextureCreationException& exception) {
        std::cerr << "failed to load texture\n";
        return 1;
    }

    VoxelsRenderer renderer;

    ChunkHeap chunks (8, 2, 8);

    MeshHeap meshes = renderer.render(chunks);

    Mesh crosshair (crosshair_vertices, 4, crosshair_attrs);

    glClearColor(0.6f,0.62f,0.65f,1);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera;

    glm::mat4 model(1.0f);

    Clock clock;

    float camX = 0, camY = 0;

    double speed = 0.01;
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
        if (window.buttonJustPressed(GLFW_MOUSE_BUTTON_1)
            || window.buttonJustPressed(GLFW_MOUSE_BUTTON_2)) {
            glm::vec3 end, norm, iend;
            Voxel* voxel = chunks.rayCast(camera.getPosition(), camera.getFront(), 10, end, norm, iend);
            if (voxel != nullptr) {
                if (window.buttonJustPressed(GLFW_MOUSE_BUTTON_1)) {
                    chunks.setVoxelGlobal((int)iend.x, (int)iend.y, (int)iend.z, 0);
                } else if (window.buttonJustPressed(GLFW_MOUSE_BUTTON_2)) {
                    int x = (int)iend.x + (int)norm.x;
                    int y = (int)iend.y + (int)norm.y;
                    int z = (int)iend.z + (int)norm.z;
                    if (!chunks.voxelNotNull(0, 0, 0, x, y, z))
                        chunks.setVoxelGlobal((int)iend.x + (int)norm.x, iend.y + (int)norm.y, iend.z + (int)norm.z, 2);
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.render(chunks, meshes);

        shader.use();
        shader.setProjView(camera.getProjView());
        texture.bind();
        for (int i = 0; i < meshes.size(); ++i) {
            shader.setModel(meshes.getModel(i));
            meshes.getMesh(i).draw();
        }
        crosshairShader.use();
        crosshair.draw(GL_LINES);

        window.swapBuffers();
    }
}