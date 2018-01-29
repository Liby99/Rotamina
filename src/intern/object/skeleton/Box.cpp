#include "object/skeleton/Box.h"

using namespace rotamina;

Box::Box() {}

Box::Box(Eigen::Vector3f boxMin, Eigen::Vector3f boxMax) {
    this->boxMin = boxMin;
    this->boxMax = boxMax;
}

Eigen::Vector3f Box::getMin() {
    return boxMin;
}

Eigen::Vector3f Box::getMax() {
    return boxMax;
}

void Box::setMin(Eigen::Vector3f boxMin) {
    this->boxMin = boxMin;
}

void Box::setMax(Eigen::Vector3f boxMax) {
    this->boxMax = boxMax;
}

void Box::draw(Shader & shader, Eigen::Matrix4f & transform) {
    
    using namespace nanogui;
    
    MatrixXu indices(3, 12);
    indices.col(0) << 0, 1, 2;
    indices.col(1) << 2, 3, 0;
    indices.col(2) << 4, 5, 6;
    indices.col(3) << 6, 7, 4;
    indices.col(4) << 8, 9, 10;
    indices.col(5) << 10, 11, 8;
    indices.col(6) << 12, 13, 14;
    indices.col(7) << 14, 15, 12;
    indices.col(8) << 16, 17, 18;
    indices.col(9) << 18, 19, 16;
    indices.col(10) << 20, 21, 22;
    indices.col(11) << 22, 23, 20;
    
    MatrixXf vertices(4, 24);
    vertices.col(0) << boxMin[0], boxMin[1], boxMin[2], 1;
    vertices.col(1) << boxMax[0], boxMin[1], boxMin[2], 1;
    vertices.col(2) << boxMax[0], boxMax[1], boxMin[2], 1;
    vertices.col(3) << boxMin[0], boxMax[1], boxMin[2], 1;
    
    vertices.col(4) << boxMin[0], boxMin[1], boxMax[2], 1;
    vertices.col(5) << boxMax[0], boxMin[1], boxMax[2], 1;
    vertices.col(6) << boxMax[0], boxMax[1], boxMax[2], 1;
    vertices.col(7) << boxMin[0], boxMax[1], boxMax[2], 1;
    
    vertices.col(8) << boxMin[0], boxMin[1], boxMin[2], 1;
    vertices.col(9) << boxMin[0], boxMin[1], boxMax[2], 1;
    vertices.col(10) << boxMin[0], boxMax[1], boxMax[2], 1;
    vertices.col(11) << boxMin[0], boxMax[1], boxMin[2], 1;
    
    vertices.col(12) << boxMax[0], boxMin[1], boxMin[2], 1;
    vertices.col(13) << boxMax[0], boxMin[1], boxMax[2], 1;
    vertices.col(14) << boxMax[0], boxMax[1], boxMax[2], 1;
    vertices.col(15) << boxMax[0], boxMax[1], boxMin[2], 1;
    
    vertices.col(16) << boxMin[0], boxMax[1], boxMin[2], 1;
    vertices.col(17) << boxMin[0], boxMax[1], boxMax[2], 1;
    vertices.col(18) << boxMax[0], boxMax[1], boxMax[2], 1;
    vertices.col(19) << boxMax[0], boxMax[1], boxMin[2], 1;
    
    vertices.col(20) << boxMin[0], boxMin[1], boxMin[2], 1;
    vertices.col(21) << boxMin[0], boxMin[1], boxMax[2], 1;
    vertices.col(22) << boxMax[0], boxMin[1], boxMax[2], 1;
    vertices.col(23) << boxMax[0], boxMin[1], boxMin[2], 1;
    
    MatrixXf normals(4, 24);
    normals.col(0) << 0, 0, -1, 1;
    normals.col(1) << 0, 0, -1, 1;
    normals.col(2) << 0, 0, -1, 1;
    normals.col(3) << 0, 0, -1, 1;
    
    normals.col(4) << 0, 0, 1, 1;
    normals.col(5) << 0, 0, 1, 1;
    normals.col(6) << 0, 0, 1, 1;
    normals.col(7) << 0, 0, 1, 1;
    
    normals.col(8) << -1, 0, 0, 1;
    normals.col(9) << -1, 0, 0, 1;
    normals.col(10) << -1, 0, 0, 1;
    normals.col(11) << -1, 0, 0, 1;
    
    normals.col(12) << 1, 0, 0, 1;
    normals.col(13) << 1, 0, 0, 1;
    normals.col(14) << 1, 0, 0, 1;
    normals.col(15) << 1, 0, 0, 1;
    
    normals.col(16) << 0, 1, 0, 1;
    normals.col(17) << 0, 1, 0, 1;
    normals.col(18) << 0, 1, 0, 1;
    normals.col(19) << 0, 1, 0, 1;
    
    normals.col(20) << 0, -1, 0, 1;
    normals.col(21) << 0, -1, 0, 1;
    normals.col(22) << 0, -1, 0, 1;
    normals.col(23) << 0, -1, 0, 1;
    
    shader.setUniform("model", transform);
    
    shader.uploadIndices(indices);
    shader.uploadAttrib("position", vertices);
    shader.uploadAttrib("normal", normals);
    
    shader.drawIndexed(GL_TRIANGLES, 0, 12);
}
