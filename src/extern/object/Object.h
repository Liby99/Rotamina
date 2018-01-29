#ifndef OBJECT_H
#define OBJECT_H

#include <nanogui/glutil.h>

#include "utility/Shader.h"
#include "utility/Transform.h"

namespace rotamina {
    class Object {
        public:
            Transform transform;
            Object();
            virtual void update();
            virtual void draw(rotamina::Shader &);
    };
}

#endif
