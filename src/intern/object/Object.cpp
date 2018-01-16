#include <iostream>
#include "object/Object.h"

using namespace rotamina;

Object::Object() {
    
}

void Object::draw() {
    
}

void Object::setShader(Shader & shader) {
    this->shader = &shader;
}
