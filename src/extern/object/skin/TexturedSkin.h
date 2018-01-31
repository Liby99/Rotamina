#ifndef TEXTURED_SKIN_H
#define TEXTURED_SKIN_H

#include "utility/Texture.h"
#include "object/skin/Skin.h"

namespace rotamina {
    class TexturedSkin : public Skin {
        protected:
            static int globalTexturePos;
            GLuint texture;
            int texturePos;
        public:
            TexturedSkin(Skeleton & skel);
            void loadTexture(const char * filename);
            virtual void draw(rotamina::Shader & shader);
    };
}

#endif
