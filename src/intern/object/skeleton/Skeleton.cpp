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

void Skeleton::update() {
    root->update(transform.getTransform());
}

void Skeleton::draw() {
    root->draw();
}
