#include "viewer/SkeletonViewer.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main () {
    Skeleton skel = SkeletonParser::loadSkeleton("../res/skeletons/horse.skel");
    SkeletonViewer::createViewer(1600, 960, "CSE 169 Project 2", skel, [&] (SkeletonViewer & viewer) {
        
    });
}
