#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <stdio.h>

namespace rotamina {
    class BMPImage {
        public:
            unsigned long sizeX;
            unsigned long sizeY;
            char * data;
            ~BMPImage();
            bool load(const char * filename);
    };
}

#endif
