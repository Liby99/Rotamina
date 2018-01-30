#include <iostream>
#include <vector>

#include "viewer/SkinViewer.h"
#include "object/skin/SkinParser.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main () {
    
    Skeleton tubeSkel = SkeletonParser::loadSkeleton("../res/skeletons/tube.skel");
    Skin tube(tubeSkel);
    SkinParser::loadSkin(tube, "../res/skins/tube_smooth.skin");
    
    SkinViewer::createViewer(1600, 960, "CSE 169 Project 2", tube, [&] (SkinViewer & v) {
        
    });
}
