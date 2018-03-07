#ifndef IK_SKELETON_H
#define IK_SKELETON_H

#include <map>
#include "object/skeleton/Skeleton.h"

namespace rotamina {
    class IKSkeleton : public Skeleton {
    public:
        std::map<Joint *, Eigen::Vector3f> targets;
        IKSkeleton();
        ~IKSkeleton();
        virtual void setTarget(Joint * j, Eigen::Vector3f t);
        virtual void removeTarget(Joint * j);
        virtual Eigen::Vector3f getTarget(Joint * j);
        virtual void update();
    private:
        float getTotalLength(Joint * joint);
    };
}

#endif
