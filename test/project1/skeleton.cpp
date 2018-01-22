#include <iostream>
#include <string>

#include "viewer/Viewer.h"
#include "object/skeleton/Skeleton.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main() {
    Skeleton skel = SkeletonParser::loadSkeleton("../res/skeletons/robot.skel");
}
