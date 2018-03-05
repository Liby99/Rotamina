#include <iostream>
#include "object/cloth/Cloth.h"

using namespace rotamina;

Cloth::Cloth(float w, float h, int sx, int sy) : width(w), height(h), subdivision(Eigen::Vector2i(sx, sy)) {
    
    // Check error
    if (sx <= 0 || sy <= 0) {
        std::cout << "Subdivision x or y cannot be 0" << std::endl;
        exit(1);
    }
    
    // Initiate Variables
    iterationCount = 2;
    springConstant = 100;
    dampingFacter = 1;
    windSpeed = Eigen::Vector3f(0, 0, 0);
    airDensity = 1.12;
    dragCoefficient = 0.2;
    groundHeight = -4;
    elasticity = 0.1;
    friction = 0.2;
    
    // Finally generate cloth
    generateCloth();
}

Cloth::~Cloth() {
    clear();
}

void Cloth::updateForce() {
    
    // First do the original update force
    ParticleSystem::updateForce();
    
    // Update Spring Damper Force
    for (int i = 0; i < springDampers.size(); i++) {
        springDampers[i]->applyForce(springConstant, dampingFacter);
    }
    
    // Update Aerodynamics Force
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i]->applyForce(windSpeed, airDensity, dragCoefficient);
    }
}

void Cloth::updateCollision() {
    for (int i = 0; i < particles.size(); i++) {
        if (particles[i]->position[1] < groundHeight) {
            particles[i]->position[1] = 2 * groundHeight - particles[i]->position[1];
            particles[i]->velocity[1] = -elasticity * particles[i]->velocity[1];
            particles[i]->velocity[0] *= (1 - friction);
            particles[i]->velocity[2] *= (1 - friction);
        }
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
    
    // Then let the shader draw the cloth
    shader.setUniform("model", transform.getTransform());
    shader.uploadIndices(indices);
    shader.uploadAttrib("position", positions);
    shader.uploadAttrib("normal", normals);
    shader.drawIndexed(GL_TRIANGLES, 0, ta);
}

void Cloth::clear() {
    
    // Remove all spring dampers
    for (int i = 0; i < springDampers.size(); i++) {
        delete springDampers[i];
    }
    springDampers.clear();
    
    // Remove all triangles
    for (int i = 0; i < triangles.size(); i++) {
        delete triangles[i];
    }
    triangles.clear();

    for (int i = 0; i < particles.size(); i++) {
        delete particles[i];
    }
    particles.clear();
}

void Cloth::reset() {
    clear();
    generateCloth();
}

void Cloth::resetFixture() {
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->fixed = false;
    }
}

void Cloth::generateCloth() {
    
    // Initiate parameters
    float sx = width / subdivision[0], sy = height / subdivision[1],
          x = -width / 2, y = height / 2;
    
    // Loop to generate particles
    for (int j = 0; j <= subdivision[1]; j++) {
        for (int i = 0; i <= subdivision[0]; i++) {
            
            // Create particle and put to the correct position
            ClothParticle * p = new ClothParticle();
            p->position = Eigen::Vector3f(x + sx * i, y - sy * j, 0);
            particles.push_back(p);
            
            // Add Spring Dampers
            if (i > 0) springDampers.push_back(new SpringDamper(*p, getParticle(i - 1, j)));
            if (j > 0) springDampers.push_back(new SpringDamper(*p, getParticle(i, j - 1)));
            if (i > 0 && j > 0) springDampers.push_back(new SpringDamper(*p, getParticle(i - 1, j - 1)));
            if (i < subdivision[0] && j > 0) springDampers.push_back(new SpringDamper(*p, getParticle(i + 1, j - 1)));
            if (i > 1) springDampers.push_back(new SpringDamper(*p, getParticle(i - 2, j)));
            if (j > 1) springDampers.push_back(new SpringDamper(*p, getParticle(i, j - 2)));
            
            // Add Cloth Triangle for Aerodynamics
            if (i > 0 && j > 0) {
                ClothParticle & p0 = getParticle(i - 1, j - 1), & p1 = getParticle(i, j - 1), & p2 = getParticle(i - 1, j);
                triangles.push_back(new ClothTriangle(p0, p1, p2));
                triangles.push_back(new ClothTriangle(p1, *p, p2));
            }
        }
    }
}

void Cloth::updateNormal() {
    for (int j = 0; j <= subdivision[1]; j++) {
        for (int i = 0; i <= subdivision[0]; i++) {
            int d = 0;
            ClothParticle & p = getParticle(i, j);
            p.normal = Eigen::Vector3f(0, 0, 0);
            if (i > 0) {
                Eigen::Vector3f ld = getParticle(i - 1, j).position - p.position;
                if (j > 0) {
                    Eigen::Vector3f ud = getParticle(i, j - 1).position - p.position;
                    p.normal += ud.cross(ld).normalized();
                    d++;
                }
                if (j < subdivision[1]) {
                    Eigen::Vector3f dd = getParticle(i, j + 1).position - p.position;
                    p.normal += ld.cross(dd).normalized();
                    d++;
                }
            }
            if (i < subdivision[0]) {
                Eigen::Vector3f rd = getParticle(i + 1, j).position - p.position;
                if (j > 0) {
                    Eigen::Vector3f ud = getParticle(i, j - 1).position - p.position;
                    p.normal += rd.cross(ud).normalized();
                    d++;
                }
                if (j < subdivision[1]) {
                    Eigen::Vector3f dd = getParticle(i, j + 1).position - p.position;
                    p.normal += dd.cross(rd).normalized();
                    d++;
                }
            }
            p.normal /= d;
        }
    }
}

ClothParticle & Cloth::getParticle(int i, int j) {
    return * (ClothParticle *) particles[getIndex(i, j)];
}

int Cloth::getIndex(int i, int j) {
    return j * (subdivision[0] + 1) + i;
}
