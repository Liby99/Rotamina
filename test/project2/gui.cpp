#include "viewer/SkeletonViewer.h"
#include "object/skeleton/SkeletonParser.h"

int main () {
    rotamina::Skeleton skel = rotamina::SkeletonParser::loadSkeleton("../res/skeletons/horse.skel");
    rotamina::SkeletonViewer::createViewer(1600, 960, "CSE 169 Project 2", skel, [&] (rotamina::SkeletonViewer & viewer) {
        
    });
}
