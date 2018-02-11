#ifndef ANIMATION_H
#define ANIMATION_H

#include "animation/Channel.h"

namespace rotamina {
    class Animation {
        protected:
            bool channelsInitiated;
            float start;
            float end;
            std::vector<Channel> channels;
        public:
            Animtaion();
            void initiateChannels(int);
            int getChannelAmount();
            Channel & getChannel(int);
            void setStartTime(float);
            void setEndTime(float);
            float getStartTime();
            float getEndTime();
    };
}

#endif
