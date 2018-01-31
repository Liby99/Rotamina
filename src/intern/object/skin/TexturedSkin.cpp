#include <iostream>

#include "object/skin/TexturedSkin.h"

using namespace rotamina;

TexturedSkin::TexturedSkin(Skeleton & skel) : Skin(skel) {
    renderTexture = true;
}

void TexturedSkin::loadTexture(const char * filename) {
    texture.load(filename);
}

void TexturedSkin::setRenderTexture(bool render) {
    this->renderTexture = render;
}

bool TexturedSkin::isRenderingTexture() {
    return renderTexture;
}

void TexturedSkin::draw(rotamina::Shader & shader) {
    
    // If render texture then
    if (this->renderTexture) {
        
        using namespace nanogui;
        
        // Set the uniform
        shader.setTexture("skinTexture", texture);
        
        // Then update the tex coordinates
        MatrixXf texCoords(2, skinVertexAmount());
        for (int i = 0; i < skinVertexAmount(); i++) {
            
            // Load texture coords
            Vector2f tc = vertices[i].getTexCoord();
            texCoords.col(i) << tc[0], tc[1];
        }
        shader.uploadAttrib("texCoord", texCoords);
    }
    
    // Let the skin to draw the rest
    Skin::draw(shader);
}
