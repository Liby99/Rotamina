#include "object/particle/Particle.h"

using namespace rotamina;

Particle::Particle() : fixed(false), mass(0.5f),
    position(Eigen::Vector3f(0, 0, 0)), velocity(Eigen::Vector3f(0, 0, 0)),
    force(Eigen::Vector3f(0, 0, 0)) {}
    
void Particle::resetForce() {
    this->force = Eigen::Vector3f(0, 0, 0);
}

void Particle::applyForce(const Eigen::Vector3f & f) {
    this->force += f;
}
    
void Particle::update(float dt) {
    if (!fixed) {
        Eigen::Vector3f a = force / mass;
        velocity += a * dt;
        position += velocity * dt;
    }
    resetForce();
}
