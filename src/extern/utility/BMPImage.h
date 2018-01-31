#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <Eigen/Dense>
#include <stdio.h>

namespace rotamina {
    class BMPImage {
        public:
            unsigned long sizeX = 0;
            unsigned long sizeY = 0;
            char * data;
            ~BMPImage();
            bool load(const char * filename);
            Eigen::Vector3f getColor(Eigen::Vector2f coord);
            Eigen::Vector3f getColor(float nx, float ny);
        private:
            float nc(char c);
    };
}

#endif
