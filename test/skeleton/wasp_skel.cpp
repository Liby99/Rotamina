#include <iostream>
#include <string>

#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    Skeleton skel = SkeletonParser::load("./res/skeletons/wasp.skel");
    SkeletonViewer::createViewer(1440, 960, "CSE 169 - Project 1 - Wasp", skel, [&](Viewer & v) {
        v.getCamera().setPosition(Eigen::Vector3f(0, 3, 3));
    });
}
