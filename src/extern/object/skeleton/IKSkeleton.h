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
        virtual void addTarget(Joint * j, Eigen::Vector3f t);
        virtual void removeTarget(Joint * j);
        virtual std::pair<Joint *, Eigen::Vector3f> getTarget(Joint * j);
        virtual void update();
    private:
        void solve();
        void forward();
        void backward();
    };
}

#endif
