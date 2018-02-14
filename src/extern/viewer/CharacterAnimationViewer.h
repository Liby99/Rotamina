#ifndef CHARACTER_ANIMATION_VIEWER
#define CHARACTER_ANIMATION_VIEWER

#include "object/animator/CharacterAnimator.h"
#include "viewer/AnimationViewer.h"

namespace rotamina {
    class CharacterAnimationViewer : public AnimationViewer {
        protected:
            CharacterAnimator * characterAnimator;
        public:
            CharacterAnimationViewer(int, int, std::string, CharacterAnimator &);
    };
}

#endif
