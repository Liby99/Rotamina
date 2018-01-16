#include <iostream>

#include "utility/Shader.h"

using namespace rotamina;

Shader * Shader::defaultShader = nullptr;

Shader::Shader() : nanogui::GLShader() {
    init(
        /* An identifying name */
        "DEFAULT_SHADER",

        /* Vertex shader */
        "#version 400\n"
        "layout(location=0) in vec3 Position;\n"
        "layout(location=1) in vec3 Normal;\n"
        "out vec3 fragPosition;\n"
        "out vec3 fragNormal;\n"
        "uniform mat4 ModelMtx=mat4(1);\n"
        "uniform mat4 ModelViewProjMtx=mat4(1);\n"
        "void main() {\n"
        "    gl_Position=ModelViewProjMtx * vec4(Position,1);\n"
        "    fragPosition=vec3(ModelMtx * vec4(Position,1));\n"
        "    fragNormal=vec3(ModelMtx * vec4(Normal,0));\n"
        "}",

        /* Fragment shader */
        "#version 400\n"
        "in vec3 fragPosition;\n"
        "in vec3 fragNormal;\n"
        "uniform vec3 AmbientColor=vec3(0.2);\n"
        "uniform vec3 LightDirection=normalize(vec3(1,5,2));\n"
        "uniform vec3 LightColor=vec3(1);\n"
        "uniform vec3 DiffuseColor=vec3(0.5);\n"
        "out vec3 finalColor;\n"
        "void main() {\n"
        "    vec3 irradiance=AmbientColor + LightColor * max(0,dot(LightDirection,fragNormal));\n"
        "    vec3 reflectance=irradiance * DiffuseColor;\n"
        "    finalColor=sqrt(reflectance);\n"
        "}"
    );
}

Shader * Shader::getDefaultShader() {
    if (!defaultShader) {
        defaultShader = new Shader();
    }
    return defaultShader;
}

void Shader::finish() {
    if (defaultShader) {
        delete defaultShader;
    }
}
