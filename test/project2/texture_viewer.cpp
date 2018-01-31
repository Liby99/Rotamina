#include <iostream>
#include "utility/Texture.h"
#include "viewer/Viewer.h"
#include "object/Object.h"

using namespace rotamina;

class Plane : public Object {
    private:
        GLuint tex;
    public:
        void initiate() {
            unsigned char pixels[] = {
                0, 0, 0,         255, 255, 255,
                255, 255, 255,   0, 0, 0
            };
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        }
        void update() {}
        void draw(Shader & shader) {
            
            // shader.setTexture("skinTexture", texture);
            // shader.setUniform("skinTexture", 0);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tex);
            glUniform1i(glGetUniformLocation(shader.getProgramId(), "skinTexture"), 0);
            
            using namespace nanogui;
            
            // Add model
            Matrix4f model;
            model.setIdentity();
            shader.setUniform("model", model);
            
            // Load data
            MatrixXu indices(3, 2);
            indices.col(0) << 0, 1, 2;
            indices.col(1) << 0, 2, 3;
            
            MatrixXf positions(3, 4);
            positions.col(0) << 1, 0, 1;
            positions.col(1) << 1, 0, -1;
            positions.col(2) << -1, 0, -1;
            positions.col(3) << -1, 0, 1;
            
            MatrixXf normals(3, 4);
            for (int i = 0; i < 4; i++)
                normals.col(i) << 0, 1, 0;
                
            MatrixXf texCoords(2, 4);
            texCoords.col(0) << 0, 0;
            texCoords.col(1) << 0, 1;
            texCoords.col(2) << 1, 1;
            texCoords.col(3) << 1, 0;
            
            // Update the parameters
            shader.uploadIndices(indices);
            shader.uploadAttrib("position", positions);
            shader.uploadAttrib("normal", normals);
            shader.uploadAttrib("texCoord", texCoords);
            shader.drawIndexed(GL_TRIANGLES, 0, 2);
        }
};

class TextureViewer : public Viewer {
    private:
        Plane plane;
    public:
        TextureViewer(int w, int h, std::string name) : Viewer(w, h, name) {
            plane.initiate();
            scene->getShader().initTwoLightsTexture();
            scene->addObject(plane);
        }
};

int main() {
    nanogui::init();
    TextureViewer v = TextureViewer(1280, 720, "Texture Test");
    v.drawAll();
    v.setVisible(true);
    nanogui::mainloop();
    nanogui::shutdown();
}
