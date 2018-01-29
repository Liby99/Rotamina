#include "object/skin/SkinVertex.h"

using namespace rotamina;

SkinVertex::SkinVertex() {}

void SkinVertex::setPosition(Eigen::Vector3f pos) {
    position = pos;
}

void SkinVertex::setNormal(Eigen::Vector3f norm) {
    normal = norm;
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
    for (int i = 0; i < weights.size(); i++) {
        m += weights[i].second * matrices[weights[i].first];
    }
    itm = m;
    itm.inverse().transpose();
    Vector4f _currPos = m * Vector4f(position[0], position[1], position[2], 1);
    Vector4f _currNorm = itm * Vector4f(normal[0], normal[1], normal[2], 1);
    currPos = Vector3f(_currPos[0], _currPos[1], _currPos[2]);
    currNorm = Vector3f(_currNorm[0], _currNorm[1], _currNorm[2]);
}
