#include <iostream>
#include <string>

#include "viewer/Viewer.h"
#include "object/Cube.h"

using namespace rotamina;

int main() {
    nanogui::init();
    
    Cube cube;
    Shader * shader;
    
    Viewer::createViewer(1440, 960, "CSE 169 - Project 1", [&](Viewer & v) {
        
        shader = new Shader();
        cube.setShader(*shader);
        
        v.getCamera().setPosition(Eigen::Vector3f(0, 0.3, 1));
        v.addObject(cube);
    });
}
