#include "object/skeleton/Skeleton.h"

using namespace rotamina;

Skeleton::Skeleton() : Object::Object() {
    root = nullptr;
}

Skeleton::~Skeleton() {
    if (root) {
        delete root;
    }
}

void Skeleton::setRoot(Joint & joint) {
    this->root = &joint;
}

Joint * Skeleton::getRoot() {
    return root;
}

void Skeleton::update() {
    Eigen::Matrix4f mat;
    mat.setIdentity();
    root->update(mat);
}

void Skeleton::draw(Shader & shader) {
    root->draw(shader);
}
