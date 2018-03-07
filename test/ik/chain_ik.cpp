#include <iostream>
#include <string>

#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    IKSkeleton skel;
    SkeletonParser::load(skel, "./res/skeletons/chain_no_constrain.skel");
    skel.setTarget(skel.getJoint(skel.jointAmount() - 1), Eigen::Vector3f(2, 2, 0));
    SkeletonViewer::createViewer(1440, 800, "CSE 169 - Final Project - Chain", skel, [&](Viewer & v) {});
}
