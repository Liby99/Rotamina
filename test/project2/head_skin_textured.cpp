#include "viewer/TexturedSkinViewer.h"
#include "object/skin/SkinParser.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main () {

    // Initiate skel and skin
    Skeleton headSkel;
    TexturedSkin headSkin = TexturedSkin(headSkel);
    SkeletonParser::loadSkeleton(headSkel, "../res/skeletons/head.skel");
    SkinParser::loadSkin(headSkin, "../res/skins/head_tex.skin");

    // Add texture to the skin
    headSkin.loadTexture("../res/textures/head.bmp");

    // Create the viewer
    TexturedSkinViewer::createViewer(1600, 960, "CSE 169 Project 2 - Head - Textured", headSkin, [&] (TexturedSkinViewer & v) {
        
    });
}
