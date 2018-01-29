#include "camera/Camera.h"

using namespace rotamina;

Camera::Camera() : Camera(960, 540) {}

Camera::Camera(int w, int h) : Camera(w, h, Eigen::Vector3f(0, 0, 1), Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(0, 1, 0)) {}

Camera::Camera(int w, int h, Eigen::Vector3f position, Eigen::Vector3f target, Eigen::Vector3f up) {
    
    // Initiate transforms
    this->width = w;
    this->height = h;
    this->position = position;
    this->target = target;
    this->up = up;
    
    // Initiate other parameters
    this->orientation = Eigen::Vector3f(0, 0, 0);
    this->zNear = 0.1f;
    this->zFar = 100.0f;
    this->fovy = M_PI / 3.0f;
}

int Camera::getWidth() const {
    return width;
}

int Camera::getHeight() const {
    return height;
}

Eigen::Matrix4f Camera::getViewPerspective() const {
    return getPerspective() * getView();
}

Eigen::Matrix4f Camera::getView() const {
    return Transform::lookAt(position, target, up);
}

Eigen::Matrix4f Camera::getPerspective() const {
    return Transform::perspective(fovy, getAspect(), zNear, zFar);
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
    return (float) width / (float) height;
}

float Camera::getFovy() const {
    return fovy;
}

void Camera::setWidth(int w) {
    this->width = w;
}

void Camera::setHeight(int h) {
    this->height = h;
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

void Camera::setFovy(float fovy) {
    this->fovy = fovy;
}
