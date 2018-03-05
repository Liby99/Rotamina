#include <iostream>
#include "object/cloth/Cloth.h"

using namespace rotamina;

Cloth::Cloth(float w, float h, int sx, int sy) :
    width(w), height(h), subdivision(Eigen::Vector2i(sx, sy)) {
    if (sx == 0 || sy == 0) {
        std::cout << "Subdivision x or y cannot be 0" << std::endl;
        exit(1);
    }
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
    float sc = 8, df = 0.05;
    float sx = width / subdivision[0], sy = height / subdivision[1], x = -width / 2, y = height / 2,
          dd = sqrt(sx * sx + sy * sy);
    for (int j = 0; j <= subdivision[1]; j++) {
        for (int i = 0; i <= subdivision[0]; i++) {
            Particle * p = new Particle();
            p->fixed = j == 0;
            p->position = Eigen::Vector3f(x + sx * i, y - sy * j, 0);
            if (i > 0) {
                springDampers.push_back(new SpringDamper(*p, getParticle(i - 1, j), sx, sc, df));
            }
            if (j > 0) {
                springDampers.push_back(new SpringDamper(*p, getParticle(i, j - 1), sy, sc, df));
            }
            if (i > 0 && j > 0) {
                springDampers.push_back(new SpringDamper(*p, getParticle(i - 1, j - 1), dd, sc, df));
            }
            if (i < subdivision[0] && j > 0) {
                springDampers.push_back(new SpringDamper(*p, getParticle(i + 1, j - 1), dd, sc, df));
            }
            if (i > 1) {
                springDampers.push_back(new SpringDamper(*p, getParticle(i - 2, j), sx * 2, sc, df));
            }
            if (j > 1) {
                springDampers.push_back(new SpringDamper(*p, getParticle(i, j - 2), sy * 2, sc, df));
            }
            particles.push_back(p);
        }
    }
}

void Cloth::updateNormal() {
    for (int j = 0; j <= subdivision[1]; j++) {
        for (int i = 0; i <= subdivision[0]; i++) {
            Eigen::Vector3f normal;
        }
    }
}

Particle & Cloth::getParticle(int i, int j) {
    return *particles[j * (subdivision[0] + 1) + i];
}

