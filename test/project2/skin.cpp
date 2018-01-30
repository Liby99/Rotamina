/**
 * Expected Initiation Scripts
 *
 * Skeleton skel = SkeletonParser::parse("sdfsdfs.skel");
 * Skin skin = SkinParser::parse("asdafsdf.skin");
 * skin.bindSkeleton(skel);
 */

#include <iostream>
#include <vector>

#include "object/skin/SkinParser.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main () {
    Skeleton tubeSkel = SkeletonParser::loadSkeleton("../res/skeletons/tube.skel");
    Skin tube(tubeSkel);
    SkinParser::loadSkin(tube, "../res/skins/tube_smooth.skin");
    std::cout << "Triangles: " << tube.triangleAmount() << std::endl;
    for (int i = 0; i < tube.skinVertexAmount(); i++) {
        std::cout << "Vertex " << i << ": " << std::endl;
        std::cout << "\tPosition: " << tube.getSkinVertex(i).getPosition() << std::endl;
        std::cout << "\tNormal: " << tube.getSkinVertex(i).getNormal() << std::endl;
    }
}
