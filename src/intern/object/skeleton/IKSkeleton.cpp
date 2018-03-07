#include "object/skeleton/IKSkeleton.h"

using namespace rotamina;

IKSkeleton::IKSkeleton() : Skeleton() {}

IKSkeleton::~IKSkeleton() : ~Skeleton() {}

void IKSkeleton::setTarget(Joint * j, Eigen::Vector3f t) {
    targets[j] = t;
}

void IKSkeleton::removeTarget(Joint * j) {
    targets.erase(j);
}

Eigen::Vector3f IKSkeleton::getTarget(Joint * j) {
    return targets[j];
}

void IKSkeleton::update() {
    // solve();
    Skeleton::update();
}

float IKSkeleton::getTotalLength(Joint * joint) {
	float length = 0;
	Joint * curr = joint;
	while (curr->hasParent()) {
		length += curr->getOffset().norm();
		curr = &curr->getParent();
	}
	return length;
}
