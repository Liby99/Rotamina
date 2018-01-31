#include <iostream>

#include "object/skin/TexturedSkin.h"

using namespace rotamina;

TexturedSkin::TexturedSkin(Skeleton & skel) : Skin(skel) {
    
}

void TexturedSkin::loadTexture(const char * filename) {
    texture.load(filename);
}

void TexturedSkin::draw(rotamina::Shader & shader) {
    
    using namespace nanogui;
    
    // Then update the tex coordinates
    MatrixXf colors(3, skinVertexAmount());
    MatrixXf texCoords(2, skinVertexAmount());
    for (int i = 0; i < skinVertexAmount(); i++) {
        
        // Load texture coords
        Vector2f tc = vertices[i].getTexCoord();
        texCoords.col(i) << tc[0], tc[1];
        
        // Load color from texture
        Vector3f color = texture.getColor(tc);
        colors.col(i) << color[0], color[1], color[2];
    }
    
    // shader.uploadAttrib("texCoord", texCoords);
    shader.uploadAttrib("color", colors);
    
    // Let the skin to draw the rest
    Skin::draw(shader);
}
