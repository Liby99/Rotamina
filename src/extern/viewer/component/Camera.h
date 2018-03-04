#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <Eigen/Dense>

#include "utility/Transform.h"

namespace rotamina {
    
    class Camera {
    private:
        
        int width;
        int height;
        
        Eigen::Vector3f position;
        Eigen::Vector3f target;
        Eigen::Vector3f up;
        Eigen::Vector3f orientation;
        
        float zNear;
        float zFar;
        float fovy;
        
    public:
        
        Camera();
        Camera(int, int);
        Camera(int, int, Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f);
        
        int getWidth() const;
        int getHeight() const;
        
        Eigen::Matrix4f getViewPerspective() const;
        Eigen::Matrix4f getView() const;
        Eigen::Matrix4f getPerspective() const;
        
        Eigen::Vector3f getPosition() const;
        Eigen::Vector3f getTarget() const;
        Eigen::Vector3f getUp() const;
        
        float getZNear() const;
        float getZFar() const;
        float getAspect() const;
        float getFovy() const;
        
        void setSize(int, int);
        void setWidth(int);
        void setHeight(int);
        
        void setPosition(Eigen::Vector3f);
        void setTarget(Eigen::Vector3f);
        void setUp(Eigen::Vector3f);
        
        void setZNear(float);
        void setZFar(float);
        void setAspect(float);
        void setFovy(float);
    };
}

#endif
