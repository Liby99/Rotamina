#ifndef BITMAP_H
#define BITMAP_H

#include <Eigen/Dense>
#include <stdio.h>

namespace rotamina {
    class Bitmap {
        public:
            
            unsigned long sizeX;
            unsigned long sizeY;
            unsigned char * data;
            
            Bitmap();
            ~Bitmap();
            bool load(const char * filename);
            Eigen::Vector3f getColor(Eigen::Vector2f coord);
            Eigen::Vector3f getColor(float nx, float ny);
        private:
            float nc(char c);
    };
}

#endif
