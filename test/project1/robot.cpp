#include <iostream>
#include <string>

#include "viewer/SkeletonViewer.h"
#include "object/Cube.h"
#include "object/skeleton/Skeleton.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main() {
    Skeleton skel = SkeletonParser::loadSkeleton("../res/skeletons/robot.skel");
    SkeletonViewer::createViewer(1440, 960, "CSE 169 - Project 1 - Robot", skel, [&](Viewer & v) {
        v.getCamera().setPosition(Eigen::Vector3f(0, 0.4, 5));
    });
}
