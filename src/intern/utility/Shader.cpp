#include <iostream>

#include "utility/Shader.h"

using namespace rotamina;

Shader::Shader() : nanogui::GLShader() {}

bool Shader::init() {
    return nanogui::GLShader::init(
        
        /* An identifying name */
        "DEFAULT_SHADER",

        /* Vertex shader */
        "#version 400\n"
        "layout(location=0) in vec3 position;\n"
        "layout(location=1) in vec3 normal;\n"
        "out vec3 fragPosition;\n"
        "out vec3 fragNormal;\n"
        "uniform mat4 model = mat4(1);\n"
        "uniform mat4 viewPersp = mat4(1);\n"
        "void main() {\n"
        "    mat4 mvp = viewPersp * model;\n"
        "    gl_Position = mvp * vec4(position, 1);\n"
        "    fragPosition = vec3(model * vec4(position, 1));\n"
        "    fragNormal = vec3(transpose(inverse(model)) * vec4(normal, 0));\n"
        "}",

        /* Fragment shader */
        "#version 400\n"
        "in vec3 fragPosition;\n"
        "in vec3 fragNormal;\n"
        "uniform vec3 AmbientColor = vec3(0.2);\n"
        "uniform vec3 LightDirection = normalize(vec3(1, 5, 2));\n"
        "uniform vec3 LightColor = vec3(1);\n"
        "uniform vec3 DiffuseColor = vec3(0.5);\n"
        "out vec4 finalColor;\n"
        "void main() {\n"
        "    vec3 irradiance = AmbientColor + LightColor * max(0, dot(LightDirection, fragNormal));\n"
        "    vec3 reflectance = irradiance * DiffuseColor;\n"
        "    finalColor = vec4(sqrt(reflectance), 1);\n"
        "}"
    );
}
