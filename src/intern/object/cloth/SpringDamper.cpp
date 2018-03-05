#include "object/cloth/SpringDamper.h"

using namespace rotamina;

SpringDamper::SpringDamper(Particle & p1, Particle & p2, float rl, float sc, float df) :
    p1(&p1), p2(&p2), restLength(rl), springConstant(sc), dampingFacter(df) {}

void SpringDamper::applyForce() {
    Eigen::Vector3f diff, e, f1, f2;
    float l, v1, v2, f;
    diff = p2->position - p1->position;
    l = diff.norm();
    e = diff / l;
    v1 = e.dot(p1->velocity);
    v2 = e.dot(p2->velocity);
    f = -springConstant * (restLength - l) - dampingFacter * (v1 - v2);
    f1 = f * e;
    f2 = -f1;
    p1->applyForce(f1);
    p2->applyForce(f2);
}
