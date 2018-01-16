#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <Eigen/Dense>

#include "utility/Transform.h"

namespace rotamina {
    
    class Camera {
        private:
            
            Eigen::Vector3f position;
            Eigen::Vector3f target;
            Eigen::Vector3f up;
            Eigen::Vector3f orientation;
            
            float zNear;
            float zFar;
            float aspect;
            float fovy;
            
        public:
            
            Camera();
            Camera(Eigen::Vector3f position, Eigen::Vector3f target, Eigen::Vector3f up);
            
            Eigen::Matrix4f getViewPerspective() const;
            Eigen::Matrix4f getView() const;
            Eigen::Matrix4f getPerspective() const;
            
            Eigen::Vector3f getPosition() const;
            Eigen::Vector3f getTarget() const;
            Eigen::Vector3f getUp() const;
            
            void setPosition(Eigen::Vector3f position);
            void setTarget(Eigen::Vector3f target);
            void setUp(Eigen::Vector3f up);
    };
}

#endif
