#include "utility/Transform.h"

using namespace rotamina;

Transform::Transform() {
    this->anchor = Eigen::Vector3f(0, 0, 0);
    this->position = Eigen::Vector3f(0, 0, 0);
    this->rotation = Eigen::Vector3f(0, 0, 0);
    this->scale = Eigen::Vector3f(1, 1, 1);
}

Eigen::Matrix4f Transform::getTransform() const {
    return getTransitionMatrix() * // Transition
           getAnchorMatrix() * // Then apply anchor
           getScaleMatrix() * getRotationMatrix() * // Then scale and rotate
           getInverseAnchorMatrix(); // First apply inverse anchor
}

Eigen::Vector3f Transform::getAnchor() const {
    return anchor;
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

void Transform::setAnchor(Eigen::Vector3f anchor) {
    this->anchor = anchor;
}

void Transform::setAnchorX(float x) {
    this->anchor[0] = x;
}

void Transform::setAnchorY(float y) {
    this->anchor[1] = y;
}

void Transform::setAnchorZ(float z) {
    this->anchor[2] = z;
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

Eigen::Matrix4f Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
    float theta = fovy / 2,
          d = cos(theta) / sin(theta),
          a = (zFar + zNear) / (zNear - zFar),
          b = 2 * zFar * zNear / (zNear - zFar);
    Eigen::Matrix4f mat;
    mat << d / aspect, 0,  0, 0,
           0,          d,  0, 0,
           0,          0,  a, b,
           0,          0, -1, 0;
    return mat;
}

Eigen::Matrix4f Transform::lookAt(const Eigen::Vector3f & position, const Eigen::Vector3f & target, const Eigen::Vector3f & up) {
    Eigen::Vector3f z = position - target,
                    y = up,
                    x = y.cross(z);
    x.normalize();
    y.normalize();
    z.normalize();
    Eigen::Matrix4f mat;
    mat << x[0], x[1], x[2], -x.dot(position),
           y[0], y[1], y[2], -y.dot(position),
           z[0], z[1], z[2], -z.dot(position),
           0, 0, 0, 1;
    return mat;
}

Eigen::Matrix4f Transform::getAnchorMatrix() const {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    mat.col(3) = Eigen::Vector4f(this->anchor[0], this->anchor[1], this->anchor[2], 1);
    return mat;
}

Eigen::Matrix4f Transform::getInverseAnchorMatrix() const {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    mat.col(3) = Eigen::Vector4f(-this->anchor[0], -this->anchor[1], -this->anchor[2], 1);
    return mat;
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
