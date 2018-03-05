#include "physics/Gravity.h"

using namespace rotamina;

const float Gravity::G = 9.8f;

Gravity::Gravity() : Gravity(G) {}

Gravity::Gravity(float g) : g(g) {}

void Gravity::applyForceTo(Particle & particle) {
    particle.applyForce(Eigen::Vector3f(0, -particle.mass * g, 0));
}
