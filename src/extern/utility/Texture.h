#ifndef TEXTURE_H
#define TEXTURE_H

#include <nanogui/opengl.h>

#include "utility/BMPImage.h"

namespace rotamina {
    class Texture {
        protected:
            static int globalPosition;
            int position;
            BMPImage image;
            GLuint textureId;
        public:
            Texture();
            Texture(const char *);
            GLuint getTextureId() const;
            void setPosition(int pos);
            int getPosition() const;
            const BMPImage & getImage() const;
            void load(const char *);
    };
}

#endif
