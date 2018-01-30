#include <iostream>
#include <vector>

#include "viewer/SkinViewer.h"
#include "object/skin/SkinParser.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main () {
    
    // Initiate skel and skin
    Skeleton headSkel;
    Skin headSkin = Skin(headSkel);
    SkeletonParser::loadSkeleton(headSkel, "../res/skeletons/head.skel");
    SkinParser::loadSkin(headSkin, "../res/skins/head_tex.skin");
    
    // Create the viewer
    SkinViewer::createViewer(1600, 960, "CSE 169 Project 2 - Head", headSkin, [&] (SkinViewer & v) {
        
    });
}
