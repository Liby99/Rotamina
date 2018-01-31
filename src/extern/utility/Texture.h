#ifndef TEXTURE_H
#define TEXTURE_H

#include <nanogui/opengl.h>

#include "utility/BMPImage.h"

namespace rotamina {
    class Texture {
        public:
            static GLuint load(const char *);
    };
}

#endif
