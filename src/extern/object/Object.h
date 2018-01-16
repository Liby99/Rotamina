#ifndef OBJECT_H
#define OBJECT_H

#include <nanogui/glutil.h>

#include "utility/Transform.h"

namespace rotamina {
    
    class Object {
        private:
            
        public:
            
            Transform transform;
            nanogui::GLShader shader;
            
            Object();
            
            Eigen::Matrix4f getTransform() const;
            void draw();
    };
}

#endif
