#ifndef TEXTURE_H
#define TEXTURE_H

#include <nanogui/opengl.h>

#include "utility/BMPImage.h"

namespace rotamina {
    class Texture {
        public:
            static void load(GLuint & t, const char *);
    };
}

#endif
