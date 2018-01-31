#include <iostream>

#include "utility/Texture.h"

using namespace rotamina;

void Texture::load(GLuint & t, const char * filename) {
    BMPImage image;
    if (!image.load(filename))
        exit(1);
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image.sizeX, image.sizeY, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
}
