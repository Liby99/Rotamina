#include <iostream>
#include <string>

#include "viewer/Viewer.h"
#include "object/Cube.h"
#include "object/skeleton/Skeleton.h"
#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

int main() {
    nanogui::init();
    
    Skeleton skel = SkeletonParser::loadSkeleton("../res/skeletons/wasp.skel");
    skel.update();
    // Cube cube;
    Shader * shader;
    
    Viewer::createViewer(1440, 960, "CSE 169 - Project 1 - Robot", [&](Viewer & v) {
        
        shader = new Shader();
        
        // cube.setShader(*shader);
        skel.setShader(*shader);
        
        v.getCamera().setPosition(Eigen::Vector3f(0, 3, 3));
        // v.addObject(cube);
        v.addObject(skel);
    });
}
