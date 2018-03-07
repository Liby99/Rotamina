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

void Joint::setParent(Joint & j) {
    this->parent = &j;
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
    return worldTransf.topRightCorner<3, 1>();
}

Eigen::Vector3f Joint::getOffset() {
    return Eigen::Vector3f(0, 0, 0);
}

std::vector<std::pair<std::string, std::string>> Joint::getVars() {
    std::vector<std::pair<std::string, std::string>> vect;
    vect.push_back(std::make_pair("World Position", vector3fToString(getGlobalPosition())));
    return vect;
}

std::string Joint::getJointType() {
    return "Joint";
}

Eigen::MatrixXf Joint::getJacobian(Joint * end) {
    Eigen::MatrixXf jacobian(3, dofs.size());
    int i = 0;
    for (auto it = dofs.begin(); it != dofs.end(); it++, i++) {
        jacobian.col(i) << getJacobianColumn(it->first, end);
    }
    return jacobian;
}

Eigen::Vector3f Joint::getJacobianColumn(std::string name, Joint * end) {
    return Eigen::Vector3f(0, 0, 0);
}

Eigen::Matrix4f Joint::getWorldTransform() {
    return worldTransf;
}

void Joint::update(const Eigen::Matrix4f & currTransf) {
    worldTransf = currTransf;
    for (rotamina::Joint * j : children) {
        j->update(currTransf);
    }
}

void Joint::draw(Shader & shader) {
    for (rotamina::Joint * j : children) {
        j->draw(shader);
    }
}

std::string Joint::vector3fToString(const Eigen::Vector3f & vec) {
    std::ostringstream os;
    os << "< " << vec[0] << ", " << vec[1] << ", " << vec[2] << " >";
    return os.str();
}

std::string Joint::limitToString(const DOF & dof) {
    std::ostringstream os;
    os << "[ " << dof.getMin() << ", " << dof.getMax() << " ]";
    return os.str();
}