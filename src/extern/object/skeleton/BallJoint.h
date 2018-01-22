#ifndef BALL_JOINT_H
#define BALL_JOINT_H

#include "object/skeleton/Joint.h"

namespace rotamina {
    
    class BallJoint : public Joint {
        protected:
            
            Eigen::Vector3f offset;
            Eigen::Vector3f boxMin;
            Eigen::Vector3f boxMax;
            
        public:
            
            BallJoint(std::string name);
            
            Eigen::Vector3f getOffset();
            Eigen::Vector3f getBoxMin();
            Eigen::Vector3f getBoxMax();
            DOF & getX();
            DOF & getY();
            DOF & getZ();
            
            void setOffset(const Eigen::Vector3f & o);
            void setBoxMin(const Eigen::Vector3f & bm);
            void setBoxMax(const Eigen::Vector3f & bm);
            void setPose(const Eigen::Vector3f & pose);
            
            virtual void draw();
    };
}

#endif
