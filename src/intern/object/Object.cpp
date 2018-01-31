#include <iostream>
#include "object/Object.h"

using namespace rotamina;

Object::Object() {
    hidden = false;
}

bool Object::isHidden() {
    return hidden;
}

void Object::setHidden(bool hidden) {
    this->hidden = hidden;
}

void Object::update() {
    // Do Nothing
}

void Object::draw(Shader & shader) {
    // Do Nothing
}
