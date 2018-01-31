#include <iostream>

#include "object/skin/TexturedSkin.h"

using namespace rotamina;

int TexturedSkin::globalTexturePos = 0;

TexturedSkin::TexturedSkin(Skeleton & skel) : Skin(skel) {
    texture = 0;
    texturePos = globalTexturePos++;
}

void TexturedSkin::loadTexture(const char * filename) {
    Texture::load(texture, filename);
}

void TexturedSkin::draw(rotamina::Shader & shader) {
    
    using namespace nanogui;
    
    // First input the texture
    glActiveTexture(GL_TEXTURE0 + texturePos);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.setUniform("skinTexture", texturePos);
    
    // Then update the tex coordinates
    MatrixXf texCoords(2, skinVertexAmount());
    for (int i = 0; i < skinVertexAmount(); i++) {
        Vector2f tc = vertices[i].getTexCoord();
        texCoords.col(i) << tc[0], tc[1];
    }
    shader.uploadAttrib("texCoord", texCoords);
    
    // Let the skin to draw the rest
    Skin::draw(shader);
}
