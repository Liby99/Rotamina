#ifndef OBJECT_H
#define OBJECT_H

#include <nanogui/glutil.h>

#include "utility/Shader.h"
#include "utility/Transform.h"

namespace rotamina {
    
    class Object {
        public:
            
            Transform transform;
            Shader shader;
            
            Object();
            
            virtual void draw();
    };
}

#endif
