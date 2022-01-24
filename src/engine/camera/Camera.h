#ifndef MINECRAFT_CAMERA_H
#define MINECRAFT_CAMERA_H

#include "../../headers/includes.h"

class Camera {

    inline static const float DEFAULT_Z_NEAR = 0.03125;
    inline static const float DEFAULT_Z_FAR = 1024;

    glm::vec3 mPosition;
    float mFieldOfView;
    float mAspect;
    float mZNear, mZFar;

    glm::vec3 mFront, mRight, mUp;
    glm::mat4 mRotation;

    float mSpeed;
    float mSensX, mSensY;

    float mRotX, mRotY;

    void updateVectors();

public:

    Camera(const glm::vec3& position = { 0, 0, 0 },
           float fieldOfView = glm::radians(70.0f),
           float aspect = 1280.0 / 720.0,
           float zNear = DEFAULT_Z_NEAR,
           float zFar = DEFAULT_Z_FAR,
           float speed = 0.01,
           float sensX = 2,
           float sensY = 2,
           float rotX = 0,
           float rotY = 0);

    void move(const glm::vec3& vec);
    void moveDirect(const glm::vec3& vec);
    void moveRelative(const glm::vec3& vec);
    void rotate(const glm::vec3& vec);

    const glm::vec3& getPosition() const;
    const glm::vec3& getFront() const;
    const glm::vec3& getUp() const;
    const glm::vec3& getRight() const;

    const glm::mat4& getRotation() const;
    void setRotation(const glm::mat4& rotation);

    float getAspect() const;
    void setAspect(float aspect);

    float getSpeed() const;
    void setSpeed(float speed);

    float getSensX() const;
    void setSensX(float sensX);
    float getSensY() const;
    void setSensY(float sensY);

    float getRotX() const;
    void setRotX(float rotX);
    void addRotX(float rotX);
    float getRotY() const;
    void setRotY(float rotY);
    void addRotY(float rotY);

    float getZNear() const;
    void setZNear(float zNear);
    float getZFar() const;
    void setZFar(float zFar);

    glm::mat4 getProjection() const;
    glm::mat4 getView() const;
    glm::mat4 getProjView() const;
};

#endif //MINECRAFT_CAMERA_H