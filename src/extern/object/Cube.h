#ifndef CUBE_H
#define CUBE_H

#include "object/Object.h";

class Cube : public Object {
    private:
        
        float width;
        float height;
        float length;
        
    public:
        
        Cube();
        Cube(float width, float height, float length);
        
        draw();
};

#endif
