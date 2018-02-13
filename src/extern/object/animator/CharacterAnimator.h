#ifndef CHARACTER_ANIMATOR_H
#define CHARACTER_ANIMATOR_H

#include "object/animator/Animator.h"

namespace rotamina {
    class CharacterAnimator : public Animator {
        protected:
            Character * character;
            std::vector<DOF *> cachedDOFs;
        public:
            CharacterAnimator(Animation &, Character &);
            virtual void updateAnimation(float);
            virtual void draw(Shader &);
        private:
            void initiateDOFs();
    };
}

#endif
