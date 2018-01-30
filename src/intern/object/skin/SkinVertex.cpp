#include <iostream>

#include "object/skin/SkinVertex.h"

using namespace rotamina;

SkinVertex::SkinVertex() {}

void SkinVertex::setPosition(Eigen::Vector3f pos) {
    position = pos;
    currPos = pos;
}

void SkinVertex::setNormal(Eigen::Vector3f norm) {
    normal = norm;
    currNorm = norm;
}

void SkinVertex::setTexCoord(Eigen::Vector2f tex) {
    texCoord = tex;
}

void SkinVertex::addWeight(int index, float weight) {
    weights.push_back(std::make_pair(index, weight));
}

Eigen::Vector3f SkinVertex::getPosition() {
    return currPos;
}

Eigen::Vector3f SkinVertex::getNormal() {
    return currNorm;
}

Eigen::Vector2f SkinVertex::getTexCoord() {
    return texCoord;
}

std::pair<int, float> & SkinVertex::getWeight(int i) {
    return weights[i];
}

std::vector<std::pair<int, float>> & SkinVertex::getWeights() {
    return weights;
}

void SkinVertex::update(std::vector<Eigen::Matrix4f> & matrices) {
    using namespace Eigen;
    Matrix4f m, itm;
    m << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
    for (int i = 0; i < weights.size(); i++) {
        m += weights[i].second * matrices[weights[i].first];
    }
    currPos = (m * Vector4f(position[0], position[1], position[2], 1)).head<3>();
    currNorm = (m.inverse().transpose() * Vector4f(normal[0], normal[1], normal[2], 0)).head<3>();
}
