#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <Eigen/Dense>

namespace rotamina {
    
    class Transform {
        public:
            
            Eigen::Vector3f anchor;
            Eigen::Vector3f position;
            Eigen::Vector3f rotation;
            Eigen::Vector3f scale;
            
            Transform();
            
            Eigen::Matrix4f getTransform() const;
            
            Eigen::Vector3f getAnchor() const;
            Eigen::Vector3f getPosition() const;
            Eigen::Vector3f getRotation() const;
            Eigen::Vector3f getScale() const;
            
            void setAnchor(Eigen::Vector3f anchor);
            void setAnchorX(float x);
            void setAnchorY(float y);
            void setAnchorZ(float z);
            
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
            
            static Eigen::Matrix4f perspective(float fovy, float aspect, float zNear, float zFar);
            static Eigen::Matrix4f lookAt(const Eigen::Vector3f & position, const Eigen::Vector3f & target, const Eigen::Vector3f & up);
            
        private:
            
            Eigen::Matrix4f getAnchorMatrix() const;
            Eigen::Matrix4f getInverseAnchorMatrix() const;
            Eigen::Matrix4f getTransitionMatrix() const;
            Eigen::Matrix4f getRotationMatrixX() const;
            Eigen::Matrix4f getRotationMatrixY() const;
            Eigen::Matrix4f getRotationMatrixZ() const;
            Eigen::Matrix4f getRotationMatrix() const;
            Eigen::Matrix4f getScaleMatrix() const;
    };
}

#endif
