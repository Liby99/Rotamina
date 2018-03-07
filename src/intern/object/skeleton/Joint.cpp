#include "object/skeleton/Joint.h"

using namespace rotamina;

Joint::Joint() : Joint("") {}

Joint::Joint(std::string name) : worldTransf(worldTransf.Identity()), parent(nullptr) {
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

bool Joint::hasParent() {
    return parent != nullptr;
}

Joint & Joint::getParent() {
    return *parent;
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

Eigen::Vector3f Joint::getGlobalPosition() {
    Eigen::Vector3f pos;
    Joint * curr = this;
    while (curr->parent) {
        pos += curr->getOffset();
        curr = curr->parent;
    }
    return pos;
}

Eigen::Vector3f Joint::getOffset() {
    return Eigen::Vector3f(0, 0, 0);
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
