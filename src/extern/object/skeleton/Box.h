#ifndef SKELETON_BOX_H
#define SKELETON_BOX_H

#include <Eigen/Dense>

#include "utility/Shader.h"

namespace rotamina {
    class Box {
    private:
        Eigen::Vector3f boxMin;
        Eigen::Vector3f boxMax;
    public:
        Box();
        Box(Eigen::Vector3f boxMin, Eigen::Vector3f boxMax);
        Eigen::Vector3f getMin();
        Eigen::Vector3f getMax();
        void setMin(Eigen::Vector3f boxMin);
        void setMax(Eigen::Vector3f boxMax);
        void draw(Shader & shader, Eigen::Matrix4f & transform);
    };
}

#endif
