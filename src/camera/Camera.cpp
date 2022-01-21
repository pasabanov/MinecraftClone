#include "Camera.h"
#include "../window/Window.h"



void Camera::updateVectors() {
    mFront = glm::vec3(mRotation * glm::vec4(0, 0, -1, 1));
    mRight = glm::vec3(mRotation * glm::vec4(-1, 0, 0, 1));
    mUp = glm::vec3(mRotation * glm::vec4(0, 1, 0, 1));
}




Camera::Camera(Window* window, const glm::vec3& position, float fieldOfView)
: mWindow(window), mPosition(position), mFieldOfView(fieldOfView), mRotation(1) {
    updateVectors();
}



void Camera::move(const glm::vec3& vec) {
    mPosition += vec;
}



void Camera::moveDirect(const glm::vec3& vec) {
    mPosition = vec;
}



void Camera::moveRelative(const glm::vec3& vec) {
    mPosition += mFront * vec.x + mRight * vec.y + mUp * vec.z;
}



void Camera::rotate(const glm::vec3& vec) {
    mRotation = glm::rotate(mRotation, vec.z, glm::vec3(0, 0, 1));
    mRotation = glm::rotate(mRotation, vec.y, glm::vec3(0, 1, 0));
    mRotation = glm::rotate(mRotation, vec.x, glm::vec3(1, 0, 0));
    updateVectors();
}



const glm::mat4& Camera::getRotation() const {
    return mRotation;
}



void Camera::setRotation(const glm::mat4& rotation) {
    mRotation = rotation;
}



glm::mat4 Camera::getProjection() const {
    float aspect = ((float) mWindow->getWidth()) / ((float) mWindow->getHeight());
    return glm::perspective(mFieldOfView, aspect, Z_NEAR, Z_FAR);
}



glm::mat4 Camera::getView() const {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}