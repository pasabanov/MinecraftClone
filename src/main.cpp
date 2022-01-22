#include "headers/includes.h"

#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture2D.h"
#include "graphics/Mesh.h"
#include "graphics/VoxelsRenderer.h"
#include "voxel/Chunk.h"
#include "camera/Camera.h"
#include "time/Clock.h"
#include "voxel/ChunkHeap.h"

int main() {

    Window window ("Window");

    Shader shader;

    try {
        shader.load("../res/shaders/main.glslv", "../res/shaders/main.glslf");
    } catch (const Shader::ShaderCreationException& exception) {
        std::cerr << "failed to load shader\n";
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

    MeshHeap meshHeap = renderer.render(chunks);

//    std::vector<Mesh> meshes;
//    std::for_each(chunks.mChunks.begin(), chunks.mChunks.end(),
//                  [&](const Chunk& ch) { meshes.push_back(renderer.render(ch)); });

    glClearColor(0.6f,0.62f,0.65f,1);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera;

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
//        shader.setModel(model);
        shader.setProjView(camera.getProjView());
        texture.bind();
        for (int i = 0; i < meshHeap.size(); ++i) {
            shader.setModel(meshHeap.getModel(i));
            meshHeap.getMesh(i).draw();
        }
//        for (int i = 0; i < meshes.size(); ++i) {
//            model = glm::mat4(1);
//            model = glm::translate(
//                    model,
//                    glm::vec3(
//                            chunks.mChunks[i].mXPos*Chunk::WIDTH,
//                            chunks.mChunks[i].mYPos*Chunk::HEIGHT,
//                            chunks.mChunks[i].mZPos*Chunk::LENGTH
//                            )
//                    );
//            shader.setModel(model);
//            meshes[i].draw(GL_TRIANGLES);
//        }

        window.swapBuffers();
    }
}