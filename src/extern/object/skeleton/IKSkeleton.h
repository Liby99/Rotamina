#ifndef IK_SKELETON_H
#define IK_SKELETON_H

#include <map>
#include "object/skeleton/Skeleton.h"

namespace rotamina {
    class IKSkeleton : public Skeleton {
    public:
        
        // Variables
        int stepCount;
        float beta, threshold;
        std::map<Joint *, Eigen::Vector3f> targets;
        
        //
        IKSkeleton();
        
        virtual void setTarget(Joint & j, Eigen::Vector3f t);
        virtual void removeTarget(Joint & j);
        virtual Eigen::Vector3f getTarget(Joint & j);
        
        virtual void update();
        
    private:
        virtual void solve();
        float getWeight(Joint *, Joint *);
    };
}

#endif
