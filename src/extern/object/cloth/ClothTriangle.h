#ifndef CLOTH_TRIANGLE_H
#define CLOTH_TRIANGLE_H

#include "object/cloth/ClothParticle.h"

namespace rotamina {
    class ClothTriangle {
    public:
        ClothParticle * p1, * p2, * p3;
        ClothTriangle(ClothParticle & p1, ClothParticle & p2, ClothParticle & p3);
        virtual void applyForce(const Eigen::Vector3f & wind, float airDensity, float dragCoef);
    };
}

#endif
