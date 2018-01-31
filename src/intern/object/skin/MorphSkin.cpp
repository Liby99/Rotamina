#include "object/skin/MorphSkin.h"

using namespace rotamina;

MorphSkin::MorphSkin(Skeleton & skel) : TexturedSkin(skel) {}

void MorphSkin::setPercentage(float p) {
    this->perc = p;
}

float MorphSkin::getPercentage() {
    return this->perc;
}

void MorphSkin::loadPosNorm(Eigen::MatrixXf & positions, Eigen::MatrixXf & normals) {
    using namespace nanogui;
    int amount = skinVertexAmount();
    positions = MatrixXf(3, amount);
    normals = MatrixXf(3, amount);
    for (int i = 0; i < amount; i++) {
        Vector3f pos = vertices[i].getPosition(perc), norm = vertices[i].getNormal(perc);
        positions.col(i) << pos[0], pos[1], pos[2];
        normals.col(i) << norm[0], norm[1], norm[2];
    }
}
