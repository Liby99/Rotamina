#ifndef CLOTH_H
#define CLOTH_H

#include "object/particle/ParticleSystem.h"
#include "object/cloth/ClothParticle.h"
#include "object/cloth/SpringDamper.h"
#include "object/cloth/ClothTriangle.h"

namespace rotamina {
    class Cloth : public ParticleSystem {
    public:
        float width, height;
        Eigen::Vector2i subdivision;
        std::vector<SpringDamper *> springDampers;
        std::vector<ClothTriangle *> triangles;
        Cloth(float w, float h, int sx, int sy);
        ~Cloth();
        virtual void updateForce();
        virtual void updateCollision();
        virtual void draw(Shader & shader);
        virtual void clear();
    private:
        void generateCloth();
        void updateNormal();
        ClothParticle & getParticle(int i, int j);
        int getIndex(int i, int j);
    };
}

#endif
