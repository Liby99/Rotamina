#include "object/skin/MorphSkin.h"

using namespace rotamina;

MorphSkin::MorphSkin(Skeleton & skel) : TexturedSkin(skel) {}

void MorphSkin::addWeight() {
    weights.push_back(0);
}

void MorphSkin::setWeight(int index, float w) {
    weights[index] = w;
}

std::vector<float> & MorphSkin::getWeights() {
    return weights;
}

float MorphSkin::getWeight(int index) {
    return weights[index];
}

void MorphSkin::loadPosNorm(Eigen::MatrixXf & positions, Eigen::MatrixXf & normals) {
    
    using namespace nanogui;
    
    // First get all morphing weights
    auto weights = getWeights();
    
    // Then initiate positions and normals
    int amount = skinVertexAmount();
    positions = MatrixXf(3, amount);
    normals = MatrixXf(3, amount);
    
    // Loop through all vertices to populate
    for (int i = 0; i < amount; i++) {
        Vector3f pos = vertices[i].getPosition(weights);
        Vector3f norm = vertices[i].getNormal(weights);
        positions.col(i) << pos[0], pos[1], pos[2];
        normals.col(i) << norm[0], norm[1], norm[2];
    }
}
