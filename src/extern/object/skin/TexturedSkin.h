#ifndef TEXTURED_SKIN_H
#define TEXTURED_SKIN_H

#include "utility/Texture.h"
#include "object/skin/Skin.h"

namespace rotamina {
    class TexturedSkin : virtual public Skin {
        protected:
            bool renderTexture;
            Texture texture;
        public:
            TexturedSkin();
            void loadTexture(const char *);
            void setRenderTexture(bool);
            bool isRenderingTexture();
            virtual void draw(rotamina::Shader &);
    };
}

#endif
