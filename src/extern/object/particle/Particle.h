#ifndef PARTICLE_H
#define PARTICLE_H

#include "object/Object.h"

namespace rotamina {
    class Particle {
    public:
        bool fixed;
        float mass;
        Eigen::Vector3f position;
        Eigen::Vector3f velocity;
        Eigen::Vector3f force;
        Particle();
        virtual void resetForce();
        virtual void applyForce(const Eigen::Vector3f & f);
        virtual void update(float dt);
    };
}

#endif
