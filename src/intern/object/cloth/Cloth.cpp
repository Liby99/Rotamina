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
    
    // Update Aerodynamics Force
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i]->applyForce(Eigen::Vector3f(10, -2.5, 7.23), 1.12, 0.2);
    }
}

void Cloth::draw(Shader & shader) {

    // First update the normals of the particles
    updateNormal();

    // Then pass in the positions, normals and indicies
    using namespace nanogui;
    int pa = particles.size(), ta = subdivision[0] * subdivision[1] * 2;
    MatrixXf positions(3, pa), normals(3, pa);
    for (int i = 0; i < pa; i++) {
        ClothParticle * cp = (ClothParticle *) particles[i];
        positions.col(i) << cp->position[0], cp->position[1], cp->position[2];
        normals.col(i) << cp->normal[0], cp->normal[1], cp->normal[2];
    }
    MatrixXu indices(3, ta);
    for (int j = 0; j < subdivision[1]; j++) {
        for (int i = 0; i < subdivision[0]; i++) {
            int index = 2 * (j * subdivision[0] + i);
            indices.col(index) << getIndex(i, j), getIndex(i, j + 1), getIndex(i + 1, j);
            indices.col(index + 1) << getIndex(i, j + 1), getIndex(i + 1, j + 1), getIndex(i + 1, j);
        }
    }

    shader.setUniform("model", transform.getTransform());
    shader.uploadIndices(indices);
    shader.uploadAttrib("position", positions);
    shader.uploadAttrib("normal", normals);
    shader.drawIndexed(GL_TRIANGLES, 0, ta);
}

void Cloth::generateCloth() {
    float sc = 35, df = 0.6;
    float sx = width / subdivision[0], sy = height / subdivision[1], x = -width / 2, y = height / 2,
          dd = sqrt(sx * sx + sy * sy);
    for (int j = 0; j <= subdivision[1]; j++) {
        for (int i = 0; i <= subdivision[0]; i++) {
            ClothParticle * p = new ClothParticle();
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
            
            if (i > 0 && j > 0) {
                ClothParticle & p0 = getParticle(i - 1, j - 1), & p1 = getParticle(i, j - 1), & p2 = getParticle(i - 1, j);
                triangles.push_back(new ClothTriangle(p0, p1, p2));
                triangles.push_back(new ClothTriangle(p1, *p, p2));
            }

            if (i > 0 && j > 0) p->normalizeFactor++;
            if (i > 0 && j < subdivision[1]) p->normalizeFactor++;
            if (i < subdivision[0] && j > 0) p->normalizeFactor++;
            if (i < subdivision[0] && j < subdivision[1]) p->normalizeFactor++;
        }
    }
}

void Cloth::updateNormal() {
    for (int j = 0; j <= subdivision[1]; j++) {
        for (int i = 0; i <= subdivision[0]; i++) {
            ClothParticle & p = getParticle(i, j);
            p.normal = Eigen::Vector3f(0, 0, 0);
            if (i > 0) {
                Particle & l = getParticle(i - 1, j);
                Eigen::Vector3f ld = l.position - p.position;
                if (j > 0) {
                    Particle & u = getParticle(i, j - 1);
                    Eigen::Vector3f ud = u.position - p.position;
                    p.normal += ud.cross(ld).normalized();
                }
                if (j < subdivision[1]) {
                    Particle & d = getParticle(i, j + 1);
                    Eigen::Vector3f dd = d.position - p.position;
                    p.normal += ld.cross(dd).normalized();
                }
            }
            if (i < subdivision[0]) {
                Particle & r = getParticle(i + 1, j);
                Eigen::Vector3f rd = r.position - p.position;
                if (j > 0) {
                    Particle & u = getParticle(i, j - 1);
                    Eigen::Vector3f ud = u.position - p.position;
                    p.normal += rd.cross(ud).normalized();
                }
                if (j < subdivision[1]) {
                    Particle & d = getParticle(i, j + 1);
                    Eigen::Vector3f dd = d.position - p.position;
                    p.normal += dd.cross(rd).normalized();
                }
            }
            p.normal /= p.normalizeFactor;
        }
    }
}

ClothParticle & Cloth::getParticle(int i, int j) {
    return * (ClothParticle *) particles[getIndex(i, j)];
}

int Cloth::getIndex(int i, int j) {
    return j * (subdivision[0] + 1) + i;
}
