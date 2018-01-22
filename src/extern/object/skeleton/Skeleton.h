#ifndef SKELETON_H
#define SKELETON_H

#include <string>

#include "object/Object.h"
#include "object/skeleton/Joint.h"

namespace rotamina {
    
    class Skeleton : public Object {
        protected:
            Joint * root;
        public:
            Skeleton();
            ~Skeleton();
            void setRoot(Joint & root);
            Joint * getRoot();
            virtual void update();
            virtual void draw();
    };
}

#endif
