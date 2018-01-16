#include "object/Object.h"

using namespace rotamina;

Object::Object() {
    shader.init(
        /* An identifying name */
        "default_shader",

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

Eigen::Matrix4f Object::getTransform() const {
    return transform.getTransform();
}

void Object::draw() {
    
    using namespace nanogui;
    
    shader.bind();
    
    MatrixXu indices(3, 2); /* Draw 2 triangles */
    indices.col(0) << 0, 1, 2;
    indices.col(1) << 2, 3, 0;
    
    MatrixXf positions(3, 4);
    positions.col(0) << -1, -1, 0;
    positions.col(1) <<  1, -1, 0;
    positions.col(2) <<  1,  1, 0;
    positions.col(3) << -1,  1, 0;
    
    MatrixXf normals(3, 4);
    normals.col(0) << 0, 0, 1;
    normals.col(1) << 0, 0, 1;
    normals.col(2) << 0, 0, 1;
    normals.col(3) << 0, 0, 1;
    
    shader.uploadIndices(indices);
    shader.uploadAttrib("Position", positions);
    shader.uploadAttrib("Normal", normals);
    
    shader.drawIndexed(GL_TRIANGLES, 0, 2);
}
