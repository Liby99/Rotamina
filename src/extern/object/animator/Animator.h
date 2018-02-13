#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "utility/StopWatch.h"
#include "animation/Animation.h"
#include "object/character/Character.h"

namespace rotamina {
    class Animator : public Object {
        protected:
            StopWatch watch;
            Animation * animation;
        public:
            Animator(Animation &);
            void start();
            void pause();
            void stop();
            bool isPlaying();
            virtual void updateAnimation(float);
            virtual void update();
            virtual void draw(Shader &);
    };
}

#endif
