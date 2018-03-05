#ifndef GRAVITY_H
#define GRAVITY_H

#include "physics/ForceField.h"

namespace rotamina {
    class Gravity : public ForceField {
    public:
        static const float G;
        float g;
        Gravity();
        Gravity(float g);
        virtual void applyForceTo(Particle & particle);
    };
}

#endif
