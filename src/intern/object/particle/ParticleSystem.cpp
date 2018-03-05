#include "object/particle/ParticleSystem.h"

using namespace rotamina;

ParticleSystem::ParticleSystem() : Object() {
    stopWatch.start();
    prevTime = stopWatch.duration();
}

ParticleSystem::~ParticleSystem() {
    clear();
}

void ParticleSystem::addForceField(ForceField & field) {
    fields.push_back(&field);
}

ForceField & ParticleSystem::getForceField(int i) {
    return *fields[i];
}

int ParticleSystem::forceFieldAmount() {
    return fields.size();
}

void ParticleSystem::updateForce() {
    for (auto part : particles) {
        for (auto field : fields) {
            field->applyForceTo(*part);
        }
    }
}

void ParticleSystem::updateCollision() {
    // Do Nothing Since No Collision
}

void ParticleSystem::update() {
    updateForce();
    float curr = stopWatch.duration(), diff = curr - prevTime;
    for (auto part : particles) {
        part->update(diff);
    }
    prevTime = curr;
    updateCollision();
}

void ParticleSystem::draw(Shader & shader) {
    using namespace nanogui;
    glPointSize(10);
    int amount = particles.size();
    MatrixXf positions(3, amount), normals(3, amount);
    for (int i = 0; i < amount; i++) {
        Vector3f p = particles[i]->position;
        positions.col(i) << p[0], p[1], p[2];
        normals.col(i) << 0, 1, 0;
    }
    Matrix4f model = transform.getTransform();
    shader.setUniform("model", model);
    shader.uploadAttrib("position", positions);
    shader.uploadAttrib("normal", normals);
    shader.drawArray(GL_POINTS, 0, particles.size());
}

void ParticleSystem::clear() {
    for (auto part : particles) {
        delete part;
    }
    particles.clear();
}
