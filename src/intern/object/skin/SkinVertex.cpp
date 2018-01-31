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

void SkinVertex::addMorphPosition() {
    addMorphPosition(position);
}

void SkinVertex::addMorphPosition(Eigen::Vector3f pos) {
    morphPositions.push_back(pos);
    currMorphPos.push_back(pos);
}

void SkinVertex::addMorphNormal() {
    addMorphNormal(normal);
}

void SkinVertex::addMorphNormal(Eigen::Vector3f norm) {
    morphNormals.push_back(norm);
    currMorphNorm.push_back(norm);
}

Eigen::Vector3f SkinVertex::getPosition(std::vector<float> & weights) {
    Eigen::Vector3f v = currPos;
    for (int i = 0; i < weights.size(); i++) {
        v += weights[i] * (currMorphPos[i] - currPos);
    }
    return v;
}

Eigen::Vector3f SkinVertex::getPosition() {
    return currPos;
}

Eigen::Vector3f SkinVertex::getOriginalPosition() {
    return position;
}

Eigen::Vector3f SkinVertex::getNormal(std::vector<float> & weights) {
    Eigen::Vector3f v = currNorm;
    for (int i = 0; i < weights.size(); i++) {
        v += weights[i] * currMorphNorm[i];
    }
    return v;
}

Eigen::Vector3f SkinVertex::getNormal() {
    return currNorm;
}

Eigen::Vector3f SkinVertex::getOriginalNormal() {
    return normal;
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
    
    // Initialize final matrix and inverse transpose matrx
    Matrix4f m, itm;
    m << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
    for (int i = 0; i < weights.size(); i++) {
        m += weights[i].second * matrices[weights[i].first];
    }
    itm = m.inverse().transpose();
    
    // Update the position and normal
    currPos = (m * Vector4f(position[0], position[1], position[2], 1)).head<3>();
    currNorm = (itm * Vector4f(normal[0], normal[1], normal[2], 0)).head<3>();
    
    // Update the morphing position and normal
    for (int i = 0; i < morphPositions.size(); i++) {
        currMorphPos[i] = (m * Vector4f(morphPositions[i][0], morphPositions[i][1], morphPositions[i][2], 1)).head<3>();
        currMorphNorm[i] = (itm * Vector4f(morphNormals[i][0], morphNormals[i][1], morphNormals[i][2], 0)).head<3>();
    }
}
