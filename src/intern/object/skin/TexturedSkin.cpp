#include "object/skin/TexturedSkin.h"

using namespace rotamina;

TexturedSkin::TexturedSkin(Skeleton & skel) : Skin(skel) {
    texture = 0;
}

void TexturedSkin::loadTexture(const char * filename) {
    texture = Texture::load(filename);
}

void TexturedSkin::draw(rotamina::Shader & shader) {
    
    using namespace nanogui;
    
    // First input the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Then update the tex coordinates
    MatrixXf texCoords(2, skinVertexAmount());
    for (int i = 0; i < skinVertexAmount(); i++) {
        Vector2f tc = vertices[i].getTexCoord();
        texCoords.col(i) << tc[0], tc[1], tc[2];
    }
    shader.uploadAttrib("texCoord", texCoords);
    
    // Let the skin to draw the rest
    Skin::draw(shader);
}
