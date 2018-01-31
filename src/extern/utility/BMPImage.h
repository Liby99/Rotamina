#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <stdio.h>

namespace rotamina {
    class BMPImage {
        public:
            unsigned long sizeX = 0;
            unsigned long sizeY = 0;
            char * data;
            ~BMPImage();
            bool load(const char * filename);
    };
}

#endif
