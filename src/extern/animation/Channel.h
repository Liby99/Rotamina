#ifndef CHANNEL_H
#define CHANNEL_H

#include <cmath>
#include <utility>
#include <vector>

#include "animation/Keyframe.h"

namespace rotamina {
    class Channel {
        public:
            enum Extrapolation { Constant, Linear, Cycle, CycleOffset, Bounce };
        protected:
            bool initiated;
            Extrapolation in;
            Extrapolation out;
            std::vector<Keyframe> keyframes;
        public:
            Channel();
            void initiateKeyframes(const int &);
            bool addKeyframe(const float &, const float &);
            bool removeKeyframe(int i);
            bool removeKeyframe(Keyframe & k);
            std::vector<Keyframe> & getKeyframes();
            int getKeyframeAmount() const;
            Keyframe & getFirstKeyframe();
            Keyframe & getKeyframe(int);
            Keyframe & getLastKeyframe();
            float getStartTime() const;
            float getEndTime() const;
            float getDuration() const;
            float getStartValue() const;
            float getEndValue() const;
            float getValueOffset() const;
            void setInExtrapolation(const Extrapolation &);
            void setOutExtrapolation(const Extrapolation &);
            Extrapolation getInExtrapolation() const;
            Extrapolation getOutExtrapolation() const;
            float evaluate(float) const;
        private:
            float evaluateBeforeStart(float t) const;
            float evaluateAfterEnd(float t) const;
            float evaluateBeforeStartLinear(float t) const;
            float evaluateBeforeStartCycle(float t) const;
            float evaluateBeforeStartCycleOffset(float t) const;
            float evaluateBeforeStartBounce(float t) const;
            float evaluateAfterEndLinear(float t) const;
            float evaluateAfterEndCycle(float t) const;
            float evaluateAfterEndCycleOffset(float t) const;
            float evaluateAfterEndBounce(float t) const;
            bool isBeforeStart(float f) const;
            bool isAfterEnd(float f) const;
            static void setPrevNext(Keyframe &, Keyframe &);
            static void setCurrPrevNext(Keyframe &, Keyframe &, Keyframe &);
    };
}

#endif
