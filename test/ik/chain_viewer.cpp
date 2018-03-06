#include <iostream>
#include <string>

#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    Skeleton skel = SkeletonParser::load("./res/skeletons/chain.skel");
    SkeletonViewer::createViewer(1440, 800, "CSE 169 - Final Project - Chain", skel, [&](Viewer & v) {
        v.getCamera().setPosition(Eigen::Vector3f(0, 25, 25));
    });
}
