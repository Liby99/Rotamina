#ifndef SPRING_DAMPER_H
#define SPRING_DAMPER_H

#include "object/cloth/ClothParticle.h"

namespace rotamina {
    class SpringDamper {
    public:
        float restLength;
        ClothParticle * p1, * p2;
        SpringDamper(ClothParticle & p1, ClothParticle & p2);
        void applyForce(float springConstant, float dampingFacter);
    };
}

#endif
