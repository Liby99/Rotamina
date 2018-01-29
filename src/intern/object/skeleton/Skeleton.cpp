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

Joint & Skeleton::getRoot() {
    return *root;
}

void Skeleton::addJoint(Joint & j) {
    joints.push_back(&j);
}

Joint & Skeleton::getJoint(int i) {
    return *(joints[i]);
}

void Skeleton::update() {
    root->update(transform.getTransform());
}

void Skeleton::draw(Shader & shader) {
    root->draw(shader);
}
