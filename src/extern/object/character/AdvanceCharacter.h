#ifndef ADVANCE_CHARACTER_H
#define ADVANCE_CHARACTER_H

#include "object/character/Character.h"
#include "object/skin/AdvanceSkin.h"

namespace rotamina {
    class AdvanceCharacter : public Character {
        protected:
            AdvanceSkin skin;
        public:
            AdvanceCharacter();
            virtual AdvanceSkin & getAdvanceSkin();
            virtual Skin & getSkin();
            virtual void drawSkin(Shader &);
    };
}

#endif
