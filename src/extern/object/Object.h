#ifndef OBJECT_H
#define OBJECT_H

#include "utility/Shader.h"
#include "utility/Transform.h"

namespace rotamina {
    class Object {
        private:
            bool hidden;
        public:
            Transform transform;
            Object();
            bool isHidden();
            void setHidden(bool);
            virtual void update();
            virtual void draw(rotamina::Shader &);
    };
}

#endif
