#ifndef CHANNEL_H
#define CHANNEL_H

#include "animation/Keyframe.h"

namespace rotamina {
    class Channel {
        public:
            enum Extrapolation { Constant, Linear, Cycle, CycleOffset, Bounce };
        protected:
            Extrapolation in;
            Extrapolation out;
            std::vector<Keyframe> keyframes;
        public:
            Channel();
            void initiateKeyframes(int);
            int getKeyframeAmount();
            Keyframe & getKeyframe(int);
            void setInExtrapolation(Extrapolation);
            void setOutExtrapolation(Extrapolation);
            Extrapolation getInExtrapolation();
            Extrapolation getOutExtrapolation();
            float evaluate(float);
        private:
    };
}

#endif
