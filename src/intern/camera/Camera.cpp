#include "camera/Camera.h"

using namespace rotamina;

Camera::Camera() : Camera(Eigen::Vector3f(0, 0, 1), Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(0, 1, 0)) {}

Camera::Camera(Eigen::Vector3f position, Eigen::Vector3f target, Eigen::Vector3f up) {
    
    // Initiate transforms
    this->position = position;
    this->target = target;
    this->up = up;
    
    // Initiate other parameters
    this->orientation = Eigen::Vector3f(0, 0, 0);
    this->zNear = 0.1f;
    this->zFar = 100.0f;
    this->aspect = (float) 960 / (float) 540;
    this->fovy = M_PI / 3.0f;
}

Eigen::Matrix4f Camera::getViewPerspective() const {
    return getPerspective() * getView();
}

Eigen::Matrix4f Camera::getView() const {
    return Transform::lookAt(position, target, up);
}

Eigen::Matrix4f Camera::getPerspective() const {
    return Transform::perspective(fovy, aspect, zNear, zFar);
}

Eigen::Vector3f Camera::getPosition() const {
    return position;
}

Eigen::Vector3f Camera::getTarget() const {
    return target;
}

Eigen::Vector3f Camera::getUp() const {
    return up;
}

float Camera::getZNear() const {
    return zNear;
}

float Camera::getZFar() const {
    return zFar;
}

float Camera::getAspect() const {
    return aspect;
}

float Camera::getFovy() const {
    return fovy;
}

void Camera::setPosition(Eigen::Vector3f position) {
    this->position = position;
}

void Camera::setTarget(Eigen::Vector3f target) {
    this->target = target;
}

void Camera::setUp(Eigen::Vector3f up) {
    this->up = up;
}

void Camera::setZNear(float zNear) {
    this->zNear = zNear;
}

void Camera::setZFar(float zFar) {
    this->zFar = zFar;
}

void Camera::setAspect(float aspect) {
    this->aspect = aspect;
}

void Camera::setFovy(float fovy) {
    this->fovy = fovy;
}
