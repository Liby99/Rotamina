#ifndef PARTICLE_H
#define PARTICLE_H

namespace rotamina {
    class Particle : public Object {
    private:
        float mass;
        Eigen::Vector3f position;
        Eigen::Vector3f velocity;
        Eigen::Vector3f force;
    public:
        Particle();
        virtual void update(float dt);
        virtual void draw(Shader & shader);
    };
}

#endif
