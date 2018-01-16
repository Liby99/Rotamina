#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense>

class Transform {
    public:
        
        Transform();
        
        Eigen::Matrix4f getTransform() const;
        
        Eigen::Vector3f getPosition() const;
        Eigen::Vector3f getRotation() const;
        Eigen::Vector3f getScale() const;
        
        void setPosition(Eigen::Vector3f position);
        void setPositionX(float x);
        void setPositionY(float y);
        void setPositionZ(float z);
        
        void setRotation(Eigen::Vector3f rotation);
        void setRotationX(float x);
        void setRotationY(float y);
        void setRotationZ(float z);
        
        void setScale(Eigen::Vector3f scale);
        void setScaleX(float x);
        void setScaleY(float y);
        void setScaleZ(float z);
        
        
    private:
        Eigen::Vector3f position;
        Eigen::Vector3f rotation;
        Eigen::Vector3f scale;
        
        Eigen::Matrix4f getTransitionMatrix() const;
        Eigen::Matrix4f getRotationMatrixX() const;
        Eigen::Matrix4f getRotationMatrixY() const;
        Eigen::Matrix4f getRotationMatrixZ() const;
        Eigen::Matrix4f getRotationMatrix() const;
        Eigen::Matrix4f getScaleMatrix() const;
};

#endif
