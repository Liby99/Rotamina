#ifndef ANIMATION_H
#define ANIMATION_H

#include "animation/Channel.h"

namespace rotamina {
    class Animation {
        protected:
            bool initiated;
            float start;
            float end;
            std::vector<Channel *> channels;
        public:
            Animation();
            ~Animation();
            void initiateChannels(int);
            int getChannelAmount() const;
            Channel & getChannel(int);
            void setStartTime(float);
            void setEndTime(float);
            float getStartTime() const;
            float getEndTime() const;
    };
}

#endif
