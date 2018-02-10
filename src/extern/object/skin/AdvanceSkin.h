#ifndef ADVANCE_SKIN_H
#define ADVANCE_SKIN_H

#include "object/skin/TexturedSkin.h"
#include "object/skin/MorphSkin.h"

namespace rotamina {
    class AdvanceSkin : public TexturedSkin, public MorphSkin {
        public:
            AdvanceSkin();
            virtual void draw(Shader &);
    };
}

#endif
