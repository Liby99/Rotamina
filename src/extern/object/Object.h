#ifndef OBJECT_H
#define OBJECT_H

#include <nanogui/glutil.h>

#include "utility/Shader.h"
#include "utility/Transform.h"

namespace rotamina {
    class Object {
        private:
            bool hidden;
            bool texture;
        public:
            Transform transform;
            Object();
            bool isHidden();
            void setHidden(bool);
            bool hasTexture();
            void setHasTexture(bool);
            virtual void update();
            virtual void draw(rotamina::Shader &);
    };
}

#endif
