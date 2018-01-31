#include <iostream>
#include <nanogui/nanogui.h>
#include "utility/Texture.h"

using namespace rotamina;

int main() {
    glfwInit();
    std::cout << "before " << std::endl;
    glEnable(GL_TEXTURE_2D);
    std::cout << "after" <<std::endl; 
    GLuint t = 0;
    Texture::load(t, "../res/textures/head.bmp");
    std::cout << t << std::endl;
}
