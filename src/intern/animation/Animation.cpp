#include "animation/Animation.h"

using namespace rotamina;

Animation::Animation() : initiated(false), start(0), end(1) {}

Animation::~Animation() {
    for (int i = 0; i < channels.size(); i++) {
        delete channels[i];
    }
}

void Animation::initiateChannels(int amount) {
    if (!initiated) {
        for (int i = 0; i < amount; i++) {
            channels.push_back(new Channel());
        }
    }
}

int Animation::getChannelAmount() const {
    return channels.size();
}

Channel & Animation::getChannel(int i) {
    return *channels[i];
}

void Animation::setStartTime(float s) {
    start = s;
}

void Animation::setEndTime(float e) {
    end = e;
}

float Animation::getStartTime() const {
    return start;
}

float Animation::getEndTime() const {
    return end;
}
