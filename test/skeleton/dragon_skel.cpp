#include <iostream>
#include <string>

#include "viewer/SkeletonViewer.h"
#include "object/Cube.h"
#include "object/skeleton/Skeleton.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main() {
    Skeleton skel = SkeletonParser::load("../res/skeletons/dragon.skel");
    SkeletonViewer::createViewer(1440, 800, "CSE 169 - Project 1 - Dragon", skel, [&](Viewer & v) {
        v.getCamera().setPosition(Eigen::Vector3f(0, 25, 25));
    });
}
