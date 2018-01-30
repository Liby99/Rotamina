#include "object/skin/Skin.h"

using namespace rotamina;

Skin::Skin(Skeleton & skeleton) {
    this->skeleton = &skeleton;
    this->verticesInitiated = false;
}

Skeleton & Skin::getSkeleton() {
    return *skeleton;
}

void Skin::initiateVertices(int size) {
    if (!verticesInitiated) {
        for (int i = 0; i < size; i++) {
            vertices.push_back(SkinVertex());
        }
        verticesInitiated = true;
    }
}

int Skin::skinVertexAmount() {
    return vertices.size();
}

SkinVertex & Skin::getSkinVertex(int i) {
    return vertices[i];
}

int Skin::triangleAmount() {
    return triangles.size();
}

void Skin::addTriangle(Eigen::Vector3i indices) {
    triangles.push_back(indices);
}

int Skin::bindingMatrixAmount() {
    return invBindings.size();
}

void Skin::addInvBinding(Eigen::Matrix4f binding) {
    binding.inverse();
    invBindings.push_back(binding);
}

void Skin::update() {
    
    // First update the skeleton
    skeleton->update();
    
    // Then calculate joint matrices
    std::vector<Eigen::Matrix4f> jointMatrices;
    int jointAmount = skeleton->jointAmount();
    for (int i = 0; i < jointAmount; i++) {
        jointMatrices.push_back(skeleton->getJoint(i).getWorldTransform() * invBindings[i]);
    }
    
    // Finally use these matrices to update the vertices
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].update(jointMatrices);
    }
}

void Skin::draw(Shader & shader) {
    
    using namespace nanogui;
    
    // Load Indices
    MatrixXu indices(3, triangleAmount());
    for (int i = 0; i < triangleAmount(); i++) {
        indices.col(i) << triangles[i][0], triangles[i][1], triangles[i][2];
    }
    
    // Load Positions and Normals
    MatrixXf positions(3, skinVertexAmount());
    MatrixXf normals(3, skinVertexAmount());
    for (int i = 0; i < skinVertexAmount(); i++) {
        Vector3f pos = vertices[i].getPosition(),
                 norm = vertices[i].getNormal();
        positions.col(i) << pos[0], pos[1], pos[2];
        normals.col(i) << norm[0], norm[1], norm[2];
    }
    
    // Finally draw the skin
    Matrix4f mat; mat.setIdentity();
    shader.setUniform("model", mat);
    shader.uploadIndices(indices);
    shader.uploadAttrib("position", positions);
    shader.uploadAttrib("normal", normals);
    shader.drawIndexed(GL_TRIANGLES, 0, triangleAmount());
}
