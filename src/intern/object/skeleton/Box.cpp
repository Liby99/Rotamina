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
    indices.col(0) << 0, 1, 2; // Left
    indices.col(1) << 1, 3, 2;
    indices.col(2) << 4, 6, 5; // Right
    indices.col(3) << 5, 6, 7;
    indices.col(4) << 0, 2, 4; // Back
    indices.col(5) << 4, 2, 6;
    indices.col(6) << 5, 3, 1; // Front
    indices.col(7) << 5, 7, 3;
    indices.col(8) << 2, 3, 7; // Up
    indices.col(9) << 6, 2, 7;
    indices.col(10) << 5, 1, 0; // Bottom
    indices.col(11) << 5, 0, 4;
    
    MatrixXf vertices(4, 8);
    vertices.col(0) << boxMin[0], boxMin[1], boxMin[2], 1;
    vertices.col(1) << boxMin[0], boxMin[1], boxMax[2], 1;
    vertices.col(2) << boxMin[0], boxMax[1], boxMin[2], 1;
    vertices.col(3) << boxMin[0], boxMax[1], boxMax[2], 1;
    vertices.col(4) << boxMax[0], boxMin[1], boxMin[2], 1;
    vertices.col(5) << boxMax[0], boxMin[1], boxMax[2], 1;
    vertices.col(6) << boxMax[0], boxMax[1], boxMin[2], 1;
    vertices.col(7) << boxMax[0], boxMax[1], boxMax[2], 1;
    vertices = transform * vertices; // Transform all points by the transform
    
    shader.uploadIndices(indices);
    shader.uploadAttrib("Position", vertices);
    
    shader.drawIndexed(GL_TRIANGLES, 0, 12);
}
