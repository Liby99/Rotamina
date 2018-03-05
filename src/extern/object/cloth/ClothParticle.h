#ifndef CLOTH_PARTICLE_H
#define CLOTH_PARTICLE_H

#include "object/particle/Particle.h"

namespace rotamina {
    class ClothParticle : public Particle {
    public:
        Eigen::Vector3f normal;
        int normalizeFactor;
        ClothParticle();
    };
}

#endif
