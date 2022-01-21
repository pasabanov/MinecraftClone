#ifndef MINECRAFT_CAMERA_H
#define MINECRAFT_CAMERA_H

#include "../headers/includes.h"

class Window; // pre-declaration

class Camera {

        inline static const float Z_NEAR = 0.1;
    inline static const float Z_FAR = 100;

    Window* mWindow;

    glm::vec3 mPosition;
    float mFieldOfView;

    glm::vec3 mFront, mRight, mUp;
    glm::mat4 mRotation;

    void updateVectors();

public:

    Camera(Window* window, const glm::vec3& position, float fieldOfView);

    void move(const glm::vec3& vec);
    void moveDirect(const glm::vec3& vec);
    void moveRelative(const glm::vec3& vec);
    void rotate(const glm::vec3& vec);

    const glm::mat4& getRotation() const;
    void setRotation(const glm::mat4& rotation);

    glm::mat4 getProjection() const;
    glm::mat4 getView() const;
};

#endif //MINECRAFT_CAMERA_H