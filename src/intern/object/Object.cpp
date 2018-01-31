#include <iostream>
#include "object/Object.h"

using namespace rotamina;

Object::Object() {
    hidden = false;
    texture = false;
}

bool Object::isHidden() {
    return hidden;
}

void Object::setHidden(bool hidden) {
    this->hidden = hidden;
}

bool Object::hasTexture() {
    return texture;
}

void Object::setHasTexture(bool texture) {
    this->texture = texture;
}

void Object::update() {
    // Do Nothing
}

void Object::draw(Shader & shader) {
    // Do Nothing
}
