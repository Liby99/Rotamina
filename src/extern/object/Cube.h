#ifndef CUBE_H
#define CUBE_H

#include "object/Object.h"

namespace rotamina {
    
    class Cube : public Object {
        protected:
            float width;
            float height;
            float length;
        public:
            Cube();
            Cube(float width, float height, float length);
            virtual void draw(rotamina::Shader &);
    };
}

#endif
