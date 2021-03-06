#include <iostream>

#include "utility/Shader.h"

using namespace rotamina;

Shader::Shader() : nanogui::GLShader() {}

GLuint Shader::getProgramId() {
    return mProgramShader;
}

bool Shader::init() {
    return nanogui::GLShader::init(
        
        "DEFAULT_SHADER",
        
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

bool Shader::initTwoLights() {
    return nanogui::GLShader::init(
        
        "TWO_LIGHT_SHADER",
        
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
        
        "#version 400\n"
        "in vec3 fragPosition;\n"
        "in vec3 fragNormal;\n"
        "uniform vec3 AmbientColor = vec3(0.3, 0.2, 0.2);\n"
        "uniform vec3 LightDirection1 = normalize(vec3(2, 1, 5));\n"
        "uniform vec3 LightColor1 = vec3(1, 0.7, 0.7);\n"
        "uniform vec3 LightDirection2 = normalize(vec3(-2, -1, -3));\n"
        "uniform vec3 LightColor2 = vec3(0.5, 0.5, 1);\n"
        "uniform vec3 DiffuseColor = vec3(0.5);\n"
        "out vec4 finalColor;\n"
        "void main() {\n"
        "    vec3 irradiance = AmbientColor + LightColor1 * max(0, dot(LightDirection1, fragNormal)) + LightColor2 * max(0, dot(LightDirection2, fragNormal));\n"
        "    vec3 reflectance = irradiance * DiffuseColor;\n"
        "    finalColor = vec4(sqrt(reflectance), 1);\n"
        "}"
    );
}

bool Shader::initTwoLightsTexture() {
    return nanogui::GLShader::init(
        
        "TWO_LIGHT_TEXTURE_SHADER",
        
        "#version 410\n"
        "layout(location=0) in vec3 position;\n"
        "layout(location=1) in vec3 normal;\n"
        "layout(location=2) in vec2 texCoord;\n"
        "out vec3 fragPosition;\n"
        "out vec3 fragNormal;\n"
        "out vec2 fragTexCoord;\n"
        "uniform mat4 model = mat4(1);\n"
        "uniform mat4 viewPersp = mat4(1);\n"
        "void main() {\n"
        "    mat4 mvp = viewPersp * model;\n"
        "    gl_Position = mvp * vec4(position, 1);\n"
        "    fragPosition = vec3(model * vec4(position, 1));\n"
        "    fragNormal = vec3(transpose(inverse(model)) * vec4(normal, 0));\n"
        "    fragTexCoord = texCoord;\n"
        "}",
        
        "#version 410\n"
        "in vec3 fragPosition;\n"
        "in vec3 fragNormal;\n"
        "in vec2 fragTexCoord;\n"
        "uniform sampler2D skinTexture;\n"
        "uniform vec3 AmbientColor = vec3(0.3, 0.2, 0.2);\n"
        "uniform vec3 LightDirection1 = normalize(vec3(2, 1, 5));\n"
        "uniform vec3 LightColor1 = vec3(1);\n"
        "uniform vec3 LightDirection2 = normalize(vec3(-2, -1, -3));\n"
        "uniform vec3 LightColor2 = vec3(1);\n"
        "uniform vec3 DiffuseColor = vec3(0.5);\n"
        "out vec4 finalColor;\n"
        "void main() {\n"
        "    vec3 irradiance = AmbientColor + LightColor1 * max(0, dot(LightDirection1, fragNormal)) + LightColor2 * max(0, dot(LightDirection2, fragNormal));\n"
        "    vec3 reflectance = irradiance * DiffuseColor;\n"
        "    finalColor = vec4(sqrt(reflectance), 1) * texture(skinTexture, fragTexCoord);\n"
        // "    finalColor = vec4(fragTexCoord, 0, 1);\n"
        "}"
    );
}

void Shader::setTexture(const std::string & name, const Texture & texture) {
    glActiveTexture(GL_TEXTURE0 + texture.getPosition());
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glUniform1i(glGetUniformLocation(getProgramId(), "skinTexture"), texture.getPosition());
}
