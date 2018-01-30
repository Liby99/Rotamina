#ifndef SKELETON_H
#define SKELETON_H

#include <string>
#include <vector>

#include "object/Object.h"
#include "object/skeleton/Joint.h"

namespace rotamina {
    class Skeleton : public Object {
        protected:
            std::vector<Joint *> joints;
            Joint * root;
        public:
            Skeleton();
            ~Skeleton();
            void setRoot(Joint & root);
            Joint & getRoot();
            int jointAmount();
            void addJoint(Joint & j);
            Joint & getJoint(int i);
            virtual void update();
            virtual void draw(rotamina::Shader &);
    };
}

#endif
