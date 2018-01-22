#include "object/skeleton/Joint.h"

using namespace rotamina;

Joint::Joint() : Joint("") {}

Joint::Joint(std::string name) {
    setName(name);
}

std::string Joint::getName() {
    return name;
}

void Joint::setName(std::string name) {
    this->name = name;
}

std::vector<std::pair<std::string, DOF *>> Joint::getDOFs() {
    std::vector<std::pair<std::string, DOF *>> ret;
    for (auto it = dofs.begin(); it != dofs.end(); it++) {
        ret.push_back(std::pair<std::string, DOF *>(it->first, it->second));
    }
    return ret;
}

void Joint::addChildren(Joint & j) {
    this->children.push_back(&j);
}

void Joint::draw() {
    // Do Nothing
}

void Joint::update(const Eigen::Matrix4f & parentTransf) {
    // Do Nothing
}
