#include "object/cloth/Cloth.h"

using namespace rotamina;

Cloth::Cloth(float w, float h, int sx, int sy) :
    width(w), height(h), subdivision(Eigen::Vector2i(sx, sy)) {
    generateCloth();
}

Cloth::~Cloth() {
    for (int i = 0; i < springDampers.size(); i++) {
        delete springDampers[i];
    }
}
    
void Cloth::updateForce() {
    
    // First do the original update force
    ParticleSystem::updateForce();
    
    // Update Spring Damper Force
    for (int i = 0; i < springDampers.size(); i++) {
        springDampers[i]->applyForce();
    }
}

void Cloth::draw(Shader & shader) {
    ParticleSystem::draw(shader);
}

void Cloth::generateCloth() {
    for (int i = 0; i <= subdivision[0]; i++) {
        for (int j = 0; j <= subdivision[1]; j++) {
            Particle * p = new Particle();
            
            particles.push_back(p);
        }
    }
}
