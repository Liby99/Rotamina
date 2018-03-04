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

void ParticleSystem::update() {
    float curr = stopWatch.duration(), diff = curr - prevTime;
    for (auto part : particles) {
        for (auto field : fields) {
            field->applyForceTo(*part);
        }
    }
    for (auto part : particles) {
        part->update(diff);
    }
    prevTime = curr;
}

void ParticleSystem::draw(Shader & shader) {
    // Do nothing
}
