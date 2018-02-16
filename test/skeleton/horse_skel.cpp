#include <iostream>
#include <string>

#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    Skeleton skel = SkeletonParser::load("./res/skeletons/horse.skel");
    SkeletonViewer::createViewer(1440, 960, "CSE 169 - Project 1 - Horse", skel, [&](Viewer & v) {
        // v.setCameraRotate(false);
        v.getCamera().setPosition(Eigen::Vector3f(3, 0, 0));
    });
}
