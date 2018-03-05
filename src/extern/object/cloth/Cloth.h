#ifndef CLOTH_H
#define CLOTH_H

#include "object/particle/ParticleSystem.h"
#include "object/cloth/SpringDamper.h"

namespace rotamina {
    class Cloth : public ParticleSystem {
    public:
        float width, height;
        Eigen::Vector2i subdivision;
        std::vector<SpringDamper *> springDampers;
        Cloth(float w, float h, int sx, int sy);
        ~Cloth();
        virtual void updateForce();
        virtual void draw(Shader & shader);
    private:
        void generateCloth();
        void updateNormal();
        Particle & getParticle(int i, int j);
    };
}

#endif
