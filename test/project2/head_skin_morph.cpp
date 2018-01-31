// #include "viewer/MorphSkinViewer.h"
#include "object/skeleton/SkeletonParser.h"
#include "object/skin/SkinParser.h"
#include "object/skin/MorphParser.h"

using namespace rotamina;

int main () {

    // Initiate skel and skin
    Skeleton headSkel;
    MorphSkin headSkin = MorphSkin(headSkel);
    SkeletonParser::loadSkeleton(headSkel, "../res/skeletons/head.skel");
    SkinParser::loadSkin(headSkin, "../res/skins/head_tex.skin");
    
    // Load the morph of the skin
    MorphParser::loadMorph(headSkin, "../res/morph/head1.morph");
    
    // Create the viewer
    // TexturedSkinViewer::createViewer(1600, 960, "CSE 169 Project 2 - Head - Textured", headSkin, [&] (TexturedSkinViewer & v) {
    //     headSkin.loadTexture("../res/textures/head.bmp");
    // });
}
