#include <iostream>
#include <string>

#include "viewer/Viewer.h"

#include "utility/Transform.h"

int main() {
    Viewer::initiate(1440, 960, "CSE 169 - Project 1", [](Viewer & v) {
        std::cout << "hHhhahaha" << std::endl;
    });
}
