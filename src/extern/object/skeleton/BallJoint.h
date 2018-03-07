#ifndef BALL_JOINT_H
#define BALL_JOINT_H

#include "Box.h"
#include "Joint.h"

namespace rotamina {
    class BallJoint : public Joint {
    protected:
        
        Eigen::Vector3f offset;
        Box box;
        
    public:
        
        BallJoint(std::string name);
        
        virtual Eigen::Vector3f getOffset();
        Eigen::Vector3f getBoxMin();
        Eigen::Vector3f getBoxMax();
        Eigen::Vector3f getPose();
        DOF & getX();
        DOF & getY();
        DOF & getZ();
        
        void setOffset(const Eigen::Vector3f & o);
        void setBoxMin(const Eigen::Vector3f & bm);
        void setBoxMax(const Eigen::Vector3f & bm);
        void setPose(const Eigen::Vector3f & pose);
        
        virtual std::vector<std::pair<std::string, std::string>> getVars();
        virtual std::string getJointType();
        
        virtual void update(const Eigen::Matrix4f & parentTransf);
        virtual void draw(Shader & shader);
    };
}

#endif
