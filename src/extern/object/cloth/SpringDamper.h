#ifndef SPRING_DAMPER_H
#define SPRING_DAMPER_H

#include "object/particle/Particle.h"

namespace rotamina {
    class SpringDamper {
    public:
        float restLength;
        float springConstant;
        float dampingFacter;
        Particle * p1, * p2;
        SpringDamper(Particle & p1, Particle & p2, float rl, float sc, float df);
        void applyForce();
    };
}

#endif
