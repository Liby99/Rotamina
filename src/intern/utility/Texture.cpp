#include <iostream>

#include "utility/Texture.h"

using namespace rotamina;

int Texture::globalPosition = 0;

Texture::Texture() {
    position = globalPosition++;
}

Texture::Texture(const char * filename) : Texture() {
    load(filename);
}

GLuint Texture::getTextureId() const {
    return textureId;
}

void Texture::setPosition(int pos) {
    position = pos;
}

int Texture::getPosition() const {
    return position;
}

const Bitmap & Texture::getImage() const {
    return image;
}

void Texture::load(const char * filename) {
    if (!image.load(filename)) {
        exit(1);
    }
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.sizeX, image.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
}
