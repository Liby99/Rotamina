#include "object/cloth/SpringDamper.h"

using namespace rotamina;

SpringDamper::SpringDamper(Particle & p1, Particle & p2, float rl, float sc, float df) :
    p1(&p1), p2(&p2), restLength(rl), springConstant(sc), dampingFacter(df) {}

void SpringDamper::applyForce() {
    Eigen::Vector3f f, x, l0, l, v;
    l = p1->position - p2->position;
    l0 = l; l0.normalize(); l0 *= restLength;
    x = l0 - l;
    v = p1->velocity - p2->velocity;
    f = -(springConstant * x + dampingFacter * v);
    p1->applyForce(f);
    p2->applyForce(-f);
}
