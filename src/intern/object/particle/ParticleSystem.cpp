#include "object/particle/ParticleSystem.h"

using namespace rotamina;

ParticleSystem::ParticleSystem() : Object() {
    stopWatch.start();
    prevTime = stopWatch.duration();
}

ParticleSystem::~ParticleSystem() {
    for (auto part : particles) {
        delete part;
    }
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

void ParticleSystem::update() {
    updateForce();
    float curr = stopWatch.duration(), diff = curr - prevTime;
    for (auto part : particles) {
        part->update(diff);
    }
    prevTime = curr;
}

void ParticleSystem::draw(Shader & shader) {
    // Do nothing
}
