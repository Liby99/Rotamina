#include "utility/Transform.h"

using namespace rotamina;

Transform::Transform() {
    this->position = Eigen::Vector3f(0, 0, 0);
    this->rotation = Eigen::Vector3f(0, 0, 0);
    this->scale = Eigen::Vector3f(1, 1, 1);
}

Eigen::Matrix4f Transform::getTransform() const {
    return getTransitionMatrix() * getScaleMatrix() * getRotationMatrix();
}

Eigen::Vector3f Transform::getPosition() const {
    return position;
}

Eigen::Vector3f Transform::getRotation() const {
    return rotation;
}

Eigen::Vector3f Transform::getScale() const {
    return scale;
}

void Transform::setPosition(Eigen::Vector3f position) {
    this->position = position;
}

void Transform::setPositionX(float x) {
    this->position[0] = x;
}

void Transform::setPositionY(float y) {
    this->position[1] = y;
}

void Transform::setPositionZ(float z) {
    this->position[2] = z;
}

void Transform::setRotation(Eigen::Vector3f rotation) {
    this->rotation = rotation;
}

void Transform::setRotationX(float x) {
    this->rotation[0] = x;
}

void Transform::setRotationY(float y) {
    this->rotation[1] = y;
}

void Transform::setRotationZ(float z) {
    this->rotation[2] = z;
}

void Transform::setScale(Eigen::Vector3f scale) {
    this->scale = scale;
}

void Transform::setScaleX(float x) {
    this->scale[0] = x;
}

void Transform::setScaleY(float y) {
    this->scale[1] = y;
}

void Transform::setScaleZ(float z) {
    this->scale[1] = z;
}

Eigen::Matrix4f Transform::getTransitionMatrix() const {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    mat.col(3) = Eigen::Vector4f(this->position[0], this->position[1], this->position[2], 1);
    return mat;
}

Eigen::Matrix4f Transform::getRotationMatrixX() const {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    mat.topLeftCorner<3, 3>() = Eigen::Matrix3f(Eigen::AngleAxisf(this->rotation[0], Eigen::Vector3f::UnitX()));
    return mat;
}

Eigen::Matrix4f Transform::getRotationMatrixY() const {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    mat.topLeftCorner<3, 3>() = Eigen::Matrix3f(Eigen::AngleAxisf(this->rotation[1], Eigen::Vector3f::UnitY()));
    return mat;
}

Eigen::Matrix4f Transform::getRotationMatrixZ() const {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    mat.topLeftCorner<3, 3>() = Eigen::Matrix3f(Eigen::AngleAxisf(this->rotation[2], Eigen::Vector3f::UnitZ()));
    return mat;
}

Eigen::Matrix4f Transform::getRotationMatrix() const {
    return getRotationMatrixZ() * getRotationMatrixY() * getRotationMatrixX();
}

Eigen::Matrix4f Transform::getScaleMatrix() const {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    mat(0, 0) = this->scale[0];
    mat(1, 1) = this->scale[1];
    mat(2, 2) = this->scale[2];
    return mat;
}
