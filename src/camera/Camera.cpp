#include "Camera.h"



void Camera::updateVectors() {
    mFront = glm::vec3(mRotation * glm::vec4(0, 0, -1, 1));
    mRight = glm::vec3(mRotation * glm::vec4(-1, 0, 0, 1));
    mUp = glm::vec3(mRotation * glm::vec4(0, 1, 0, 1));
}




Camera::Camera(const glm::vec3& position, float fieldOfView, float aspect, float zNear, float zFar)
: mPosition(position), mFieldOfView(fieldOfView), mAspect(aspect), mZNear(zNear), mZFar(zFar), mRotation(1) {
    updateVectors();
}



void Camera::move(const glm::vec3& vec) {
    mPosition = vec;
}

void Camera::moveDirect(const glm::vec3& vec) {
    mPosition += vec;
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



const glm::vec3& Camera::getPosition() const {
    return mPosition;
}

const glm::vec3& Camera::getFront() const {
    return mFront;
}

const glm::vec3& Camera::getUp() const {
    return mUp;
}

const glm::vec3& Camera::getRight() const {
    return mRight;
}



const glm::mat4& Camera::getRotation() const {
    return mRotation;
}

void Camera::setRotation(const glm::mat4& rotation) {
    mRotation = rotation;
}



float Camera::getAspect() const {
    return mAspect;
}

void Camera::setAspect(float aspect) {
    mAspect = aspect;
}



float Camera::getZNear() const {
    return mZNear;
}

void Camera::setZNear(float zNear) {
    mZNear = zNear;
}

float Camera::getZFar() const {
    return mZFar;
}

void Camera::setZFar(float zFar) {
    mZFar = zFar;
}



glm::mat4 Camera::getProjection() const {
    return glm::perspective(mFieldOfView, mAspect, mZNear, mZFar);
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 Camera::getProjView() const {
    return getProjection() * getView();
}