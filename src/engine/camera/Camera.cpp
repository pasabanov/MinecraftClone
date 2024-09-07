/*
 * MinecraftClone
 * Copyright (C) © 2022  Petr Alexandrovich Sabanov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <engine/camera/Camera.h>

void Camera::updateVectors() {
	mFront = glm::vec3(mRotation * glm::vec4(0, 0, -1, 1));
	mRight = glm::vec3(mRotation * glm::vec4(-1, 0, 0, 1));
	mUp = glm::vec3(mRotation * glm::vec4(0, 1, 0, 1));
}

Camera::Camera(
		const glm::vec3& position,
		float fieldOfView,
		float aspect,
		float zNear,
		float zFar,
		float speed,
		float sensX,
		float sensY,
		float rotX,
		float rotY)
: mPosition(position), mFieldOfView(fieldOfView), mAspect(aspect)
, mZNear(zNear), mZFar(zFar), mRotation(1),
  mSpeed(speed), mSensX(sensX), mSensY(sensY),
  mRotX(rotX), mRotY(rotY) {
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

float Camera::getSpeed() const {
	return mSpeed;
}

void Camera::setSpeed(float speed) {
	mSpeed = speed;
}

float Camera::getSensX() const {
	return mSensX;
}

void Camera::setSensX(float sensX) {
	mSensX = sensX;
}

float Camera::getSensY() const {
	return mSensY;
}

void Camera::setSensY(float sensY) {
	mSensY = sensY;
}

float Camera::getRotX() const {
	return mRotX;
}

void Camera::setRotX(float rotX) {
	mRotX = rotX;
}

void Camera::addRotX(float rotX) {
	mRotX += rotX;
}

float Camera::getRotY() const {
	return mRotY;
}

void Camera::setRotY(float rotY) {
	mRotY = rotY;
}

void Camera::addRotY(float rotY) {
	mRotY += rotY;
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