#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <vector>

#include "utility/StopWatch.h"
#include "physics/ForceField.h"
#include "object/particle/Particle.h"

namespace rotamina {
    class ParticleSystem : public Object {
    public:
        std::vector<ForceField *> fields;
        std::vector<Particle *> particles;
        StopWatch stopWatch;
    private:
        float prevTime;
    public:
        ParticleSystem();
        ~ParticleSystem();
        void addForceField(ForceField & field);
        ForceField & getForceField(int i);
        int forceFieldAmount();
        virtual void updateForce();
        virtual void update();
        virtual void draw(Shader & shader);
    };
}

#endif
