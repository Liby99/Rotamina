#include "object/skeleton/IKSkeleton.h"

using namespace rotamina;

IKSkeleton::IKSkeleton() : Skeleton(), stepCount(1), beta(0.1f) {}

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
    solve();
    Skeleton::update();
}

void IKSkeleton::solve() {

    // First start iteration step
    for (int i = 0; i < stepCount; i++) {

        // Go through every joint
        for (Joint * j : joints) {

            // Loop through multiple targets
            for (auto it = targets.begin(); it != targets.end(); it++) {

                // Loop through joint dofs
                for (auto dp : j->getDOFs()) {

                    Eigen::Vector3f col = j->getJacobianColumn(dp.first, it->first);
                    Eigen::Vector3f de = beta * (it->second - it->first->getGlobalPosition());
                    float change = col.dot(de);
                    dp.second->setValue(dp.second->getValue() + change);

                    Skeleton::update();
                }
            }
        }
    }
}
