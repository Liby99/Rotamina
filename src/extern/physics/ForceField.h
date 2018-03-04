#ifndef FORCE_FIELD_H
#define FORCE_FIELD_H

#include "object/particle/Particle.h"

namespace rotamina {
    class ForceField {
    public:
        virtual void applyForceTo(Particle & particle);
    };
}

#endif
