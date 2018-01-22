#include <iostream>
#include <string>

#include "viewer/Viewer.h"
#include "object/Cube.h"

using namespace rotamina;

int main() {
    nanogui::init();
    
    nanogui::GLShader mShader;
    
    // mShader.init(
    //     /* An identifying name */
    //     "a_simple_shader",
    //
    //     /* Vertex shader */
    //     "#version 330\n"
    //     "uniform mat4 modelViewProj;\n"
    //     "in vec3 position;\n"
    //     "void main() {\n"
    //     "    gl_Position = modelViewProj * vec4(position, 1.0);\n"
    //     "}",
    //
    //     /* Fragment shader */
    //     "#version 330\n"
    //     "out vec4 color;\n"
    //     "uniform float intensity;\n"
    //     "void main() {\n"
    //     "    color = vec4(vec3(intensity), 1.0);\n"
    //     "}"
    // );
}
