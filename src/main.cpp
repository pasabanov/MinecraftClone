#include <chrono>
#include "headers/includes.h"

#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "camera/Camera.h"
#include "clock/Clock.h"

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
        // x    y     z     u     v
        -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int main() {

    Window window (WIDTH, HEIGHT, "Window");

    glClearColor(0, 0, 0, 1);

    Shader shader;

    try {
        shader.load("../res/shaders/main.glslv", "../res/shaders/main.glslf");
    } catch (const Shader::ShaderCreationException& exception) {
        std::cerr << "failed to load shader\n";
        return 1;
    }

    Texture texture;

    try {
        texture.load("../res/images/img2.png");
    } catch (const Texture::TextureCreationException& exception) {
        std::cerr << "failed to load texture\n";
        return 1;
    }

    // Create VAO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // mPosition
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glClearColor(0.6f,0.62f,0.65f,1);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera (&window, glm::vec3(0, 0, 1), glm::radians(70.0f));

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.5, 0, 0));

    Clock clock;

    float camX = 0, camY = 0;

    while(!window.isShouldClose()) {

        double speed = 0.002;
        long elapsedTime = clock.elapsedTimeMillis();

        window.pollEvents();
        if (window.keyJustPressed(GLFW_KEY_ESCAPE)) {
            window.setShouldClose(true);
        }
        if (window.keyJustPressed(GLFW_KEY_TAB)) {
            window.toggleCursor();
        }
        if (window.buttonJustPressed(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(1, 0, 0, 1);
        }
        if (window.keyPressed(GLFW_KEY_W)) {
            camera.moveRelative(glm::vec3(-elapsedTime * speed, 0, 0));
        }
        if (window.keyPressed(GLFW_KEY_S)) {
            camera.moveRelative(glm::vec3(elapsedTime * speed, 0, 0));
        }
        if (window.keyPressed(GLFW_KEY_A)) {
            camera.moveRelative(glm::vec3(0, -elapsedTime * speed, 0));
        }
        if (window.keyPressed(GLFW_KEY_D)) {
            camera.moveRelative(glm::vec3(0, elapsedTime * speed, 0));
        }
        if (window.keyPressed(GLFW_KEY_SPACE)) {
            camera.move(glm::vec3(0, -elapsedTime * speed, 0));
        }
        if (window.keyPressed(GLFW_KEY_LEFT_CONTROL)) {
            camera.move(glm::vec3(0, elapsedTime * speed, 0));
        }
        if (window.mCursorDisabled) {
            camX += -window.mDeltaX / window.getWidth();
            camY += -window.mDeltaY / window.getHeight();
            if (camY < -glm::radians(89.0f))
                camY = -glm::radians(89.0f);
            else if (camY > glm::radians(89.0f))
                camY = glm::radians(89.0f);
            camera.setRotation(glm::mat4(1));
            camera.rotate(glm::vec3(camY, camX, 0));
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.uniformMatrix("model", model);
        shader.uniformMatrix("projview", camera.getProjection() * camera.getView());
        texture.bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        window.swapBuffers();
    }
}