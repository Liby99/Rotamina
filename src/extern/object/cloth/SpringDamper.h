#ifndef SPRING_DAMPER_H
#define SPRING_DAMPER_H

#include "object/cloth/ClothParticle.h"

namespace rotamina {
    class SpringDamper {
    public:
        float restLength;
        float springConstant;
        float dampingFacter;
        ClothParticle * p1, * p2;
        SpringDamper(ClothParticle & p1, ClothParticle & p2, float rl, float sc, float df);
        void applyForce();
    };
}

#endif
