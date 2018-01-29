#include <iostream>
#include <string>

#include "viewer/Viewer.h"
#include "object/Cube.h"

using namespace rotamina;

int main() {
    Cube cube;
    Viewer::createViewer(1440, 960, "CSE 169 - Project 1", [&](Viewer & v) {
        v.getCamera().setPosition(Eigen::Vector3f(0, 0.3, 1));
        v.addObject(cube);
    });
}
