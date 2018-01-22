#include "object/skeleton/BallJoint.h"

using namespace rotamina;

BallJoint::BallJoint(std::string name) : Joint::Joint(name) {
    dofs["x"] = new DOF(0, 0);
    dofs["y"] = new DOF(0, 0);
    dofs["z"] = new DOF(0, 0);
}

Eigen::Vector3f BallJoint::getOffset() {
    return this->offset;
}

Eigen::Vector3f BallJoint::getBoxMin() {
    return this->boxMin;
}

Eigen::Vector3f BallJoint::getBoxMax() {
    return this->boxMax;
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
    this->offset = o;
}

void BallJoint::setBoxMin(const Eigen::Vector3f & bm) {
    this->boxMin = bm;
}

void BallJoint::setBoxMax(const Eigen::Vector3f & bm) {
    this->boxMax = bm;
}

void BallJoint::setPose(const Eigen::Vector3f & pose) {
    dofs["x"]->setValue(pose[0]);
    dofs["y"]->setValue(pose[1]);
    dofs["z"]->setValue(pose[2]);
}

void BallJoint::draw() {
    
}
