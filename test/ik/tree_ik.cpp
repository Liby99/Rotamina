#include <iostream>
#include <string>

#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    IKSkeleton skel;
    SkeletonParser::load(skel, "./res/skeletons/tree.skel");
    skel.setTarget(skel.getJoint(5), Eigen::Vector3f(-4, 6, 0));
    skel.setTarget(skel.getJoint(9), Eigen::Vector3f(4, 6, 0));
    IKViewer::createViewer(1440, 800, "CSE 169 - Final Project - Tree", skel);
}
