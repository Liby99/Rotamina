#include "object/cloth/ClothTriangle.h"

using namespace rotamina;

ClothTriangle::ClothTriangle(ClothParticle & p1, ClothParticle & p2, ClothParticle & p3) : p1(&p1), p2(&p2), p3(&p3) {}

void ClothTriangle::applyForce(const Eigen::Vector3f & wind, float airDensity, float dragCoef) {
    Eigen::Vector3f vs, d21, d31, c, n, f;
    vs = (p1->velocity + p2->velocity + p3->velocity) / 3;
    d21 = (p2->position - p1->position);
    d31 = (p3->position - p1->position);
    c = d21.cross(d31);
    n = c.normalized();
    float a = d21.cross(d31).norm() / 2 * wind.normalized().dot(n);
    f = -airDensity * (vs - wind).squaredNorm() * dragCoef * a * n / 6;
    p1->applyForce(f);
    p2->applyForce(f);
    p3->applyForce(f);
}
