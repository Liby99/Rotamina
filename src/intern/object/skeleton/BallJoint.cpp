#include <iostream>
#include "object/skeleton/BallJoint.h"

using namespace rotamina;

BallJoint::BallJoint(std::string name) : Joint::Joint(name) {
    dofs["x"] = new DOF();
    dofs["y"] = new DOF();
    dofs["z"] = new DOF();
}

Eigen::Vector3f BallJoint::getOffset() {
    return offset;
}

Eigen::Vector3f BallJoint::getBoxMin() {
    return box.getMin();
}

Eigen::Vector3f BallJoint::getBoxMax() {
    return box.getMax();
}

Eigen::Vector3f BallJoint::getPose() {
    return Eigen::Vector3f(dofs["x"]->getValue(), dofs["y"]->getValue(), dofs["z"]->getValue());
}

DOF & BallJoint::getX() {
    return *dofs["x"];
}

DOF & BallJoint::getY() {
    return *dofs["y"];
}

DOF & BallJoint::getZ() {
    return *dofs["z"];
}

void BallJoint::setOffset(const Eigen::Vector3f & o) {
    offset = o;
}

void BallJoint::setBoxMin(const Eigen::Vector3f & bm) {
    box.setMin(bm);
}

void BallJoint::setBoxMax(const Eigen::Vector3f & bm) {
    box.setMax(bm);
}

void BallJoint::setPose(const Eigen::Vector3f & pose) {
    dofs["x"]->setValue(pose[0]);
    dofs["y"]->setValue(pose[1]);
    dofs["z"]->setValue(pose[2]);
}

std::string vector3fToString(const Eigen::Vector3f & vec) {
    std::ostringstream os;
    os << "< " << vec[0] << ", " << vec[1] << ", " << vec[2] << " >";
    return os.str();
}

std::string limitToString(const DOF & dof) {
    std::ostringstream os;
    os << "[ " << dof.getMin() << ", " << dof.getMax() << " ]";
    return os.str();
}

std::vector<std::pair<std::string, std::string>> BallJoint::getVars() {
    std::vector<std::pair<std::string, std::string>> vect;
    vect.push_back(std::make_pair("Offset", vector3fToString(offset)));
    vect.push_back(std::make_pair("Box Min", vector3fToString(getBoxMin())));
    vect.push_back(std::make_pair("Box Max", vector3fToString(getBoxMax())));
    vect.push_back(std::make_pair("X Limit", limitToString(*dofs["x"])));
    vect.push_back(std::make_pair("Y Limit", limitToString(*dofs["y"])));
    vect.push_back(std::make_pair("Z Limit", limitToString(*dofs["z"])));
    return vect;
}

std::string BallJoint::getJointType() {
    return "Ball Joint";
}

void BallJoint::update(const Eigen::Matrix4f & parentTransf) {
    rotamina::Transform transf;
    transf.setPosition(offset);
    transf.setRotationX(dofs["x"]->getValue());
    transf.setRotationY(dofs["y"]->getValue());
    transf.setRotationZ(dofs["z"]->getValue());
    worldTransf = parentTransf * transf.getTransform();
    Joint::update(worldTransf);
}

void BallJoint::draw(Shader & shader) {
    box.draw(shader, worldTransf);
    Joint::draw(shader);
}

Eigen::Vector3f BallJoint::getJacobianColumn(std::string name, Joint * end) {
    Eigen::Vector4f a(0, 0, 0);
    if (name == "x") a[0] = 1;
    else if (name == "y") a[1] = 1;
    else if (name == "z") a[2] = 1;
    return a.cross(end->getGlobalPosition() - getGlobalPosition());
}
