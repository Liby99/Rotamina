#include "object/skeleton/Joint.h"

using namespace rotamina;

Joint::Joint() : Joint("") {}

Joint::Joint(std::string name) {
    setName(name);
}

Joint::~Joint() {
    for (Joint * j : children) {
        delete j;
    }
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
    children.push_back(&j);
}

std::vector<rotamina::Joint *> Joint::getChildren() {
    return children;
}

int Joint::childrenCount() {
    return children.size();
}

std::vector<std::pair<std::string, std::string>> Joint::getVars() {
    return std::vector<std::pair<std::string, std::string>>();
}

std::string Joint::getJointType() {
    return "Joint";
}

Eigen::Matrix4f Joint::getWorldTransform() {
    return worldTransf;
}

void Joint::update(const Eigen::Matrix4f & currTransf) {
    for (rotamina::Joint * j : children) {
        j->update(currTransf);
    }
}

void Joint::draw(Shader & shader) {
    for (rotamina::Joint * j : children) {
        j->draw(shader);
    }
}
