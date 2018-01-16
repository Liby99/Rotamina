#include <iostream>
#include <string>
#include <cmath>

#include "utility/Transform.h"

using namespace rotamina;

int main() {
    auto t = Transform();
    t.setPositionX(3);
    t.setPositionY(3);
    t.setPositionZ(5);
    
    t.setRotationY(M_PI / 2);
    
    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    std::cout << t.getTransform().format(CleanFmt) << std::endl;
}
