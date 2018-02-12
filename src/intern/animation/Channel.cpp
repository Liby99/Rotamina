#include "animation/Channel.h"

using namespace rotamina;

Channel::Channel() : in(Extrapolation::Constant), out(Extrapolation::Constant), initiated(false) {}

void Channel::initiateKeyframes(const int & amount) {
    if (!initiated) {
        for (int i = 0; i < amount; i++) {
            keyframes.push_back(Keyframe());
            if (i != 0) {
                setPrevNext(keyframes[i - 1], keyframes[i]);
            }
        }
        initiated = true;
    }
}

bool Channel::addKeyframe(const float & t, const float & v) {
    if (keyframes.size() == 0) {
        keyframes.push_back(Keyframe(t, v));
    }
    else if (keyframes.size() == 1) {
        if (t == keyframes[0].getTime()) {
            return false;
        }
        else if (t > keyframes[0].getTime()) {
            keyframes.push_back(Keyframe(t, v));
        }
        else {
            keyframes.insert(keyframes.begin(), Keyframe(t, v));
        }
        setPrevNext(keyframes[0], keyframes[1]);
    }
    else {
        if (t < keyframes[0].getTime()) {
            keyframes.insert(keyframes.begin(), Keyframe(t, v));
            setPrevNext(keyframes[0], keyframes[1]);
        }
        else if (t > keyframes[keyframes.size() - 1].getTime()) {
            keyframes.push_back(Keyframe(t, v));
            setPrevNext(keyframes[keyframes.size() - 2], keyframes[keyframes.size() - 1]);
        }
        else {
            int start = 0, end = keyframes.size() - 1, mid = 0;
            while (start < end - 1) {
                mid = (end - start) / 2;
                if (t == keyframes[start].getTime() ||
                    t == keyframes[mid].getTime() ||
                    t == keyframes[end].getTime()) {
                    return false;
                }
                else if (t > keyframes[mid].getTime()) {
                    start = mid;
                }
                else {
                    end = mid;
                }
            }
            keyframes.insert(keyframes.begin() + start, Keyframe(t, v));
            setCurrPrevNext(keyframes[start], keyframes[start + 1], keyframes[start + 2]);
        }
    }
    return true;
}

void Channel::removeKeyframe(int i) {
    removeKeyframe(keyframes[i]);
}

void Channel::removeKeyframe(Keyframe & k) {
    int s = 0, e = keyframes.size() - 1, m = 0, tt = k.getTime();
    while (s != e) {
        m = (e - s) / 2;
        float mt = keyframes[m].getTime();
        if (mt == tt) {
            break;
        }
        else if (mt > tt) {
            s = m;
        }
        else {
            e = m;
        }
    }
    
}

std::vector<Keyframe> & Channel::getKeyframes() {
    return keyframes;
}

int Channel::getKeyframeAmount() const {
    return keyframes.size();
}

const Keyframe & Channel::getFirstKeyframe() const {
    return keyframes[0];
}

const Keyframe & Channel::getKeyframe(int i) const {
    return keyframes[i];
}

const Keyframe & Channel::getLastKeyframe() const {
    return keyframes[keyframes.size() - 1];
}

float Channel::getStartTime() const {
    return getFirstKeyframe().getTime();
}

float Channel::getEndTime() const {
    return getLastKeyframe().getTime();
}

float Channel::getDuration() const {
    return getEndTime() - getStartTime();
}

float Channel::getStartValue() const {
    return getFirstKeyframe().getValue();
}

float Channel::getEndValue() const {
    return getLastKeyframe().getValue();
}

float Channel::getValueOffset() const {
    return getLastKeyframe().getValue() - getFirstKeyframe().getValue();
}

void Channel::setInExtrapolation(const Channel::Extrapolation & in) {
    this->in = in;
}

void Channel::setOutExtrapolation(const Channel::Extrapolation & out) {
    this->out = out;
}

Channel::Extrapolation Channel::getInExtrapolation() const {
    return this->in;
}

Channel::Extrapolation Channel::getOutExtrapolation() const {
    return this->out;
}

float Channel::evaluate(float t) const {
    if (isBeforeStart(t)) {
        return evaluateBeforeStart(t);
    }
    else if (isAfterEnd(t)) {
        return evaluateAfterEnd(t);
    }
    else {
        return 0;
    }
}

float Channel::evaluateBeforeStart(float t) const {
    switch (in) {
        case Extrapolation::Constant: return getStartValue();
        case Extrapolation::Linear: return evaluateBeforeStartLinear(t);
        case Extrapolation::Cycle: return evaluateBeforeStartCycle(t);
        case Extrapolation::CycleOffset: return evaluateBeforeStartCycleOffset(t);
        case Extrapolation::Bounce: return evaluateBeforeStartBounce(t);
        default: return 0;
    }
}

float Channel::evaluateAfterEnd(float t) const {
    switch (out) {
        case Extrapolation::Constant: return getEndValue();
        case Extrapolation::Linear: return evaluateAfterEndLinear(t);
        case Extrapolation::Cycle: return evaluateAfterEndCycle(t);
        case Extrapolation::CycleOffset: return evaluateAfterEndCycleOffset(t);
        case Extrapolation::Bounce: return evaluateAfterEndBounce(t);
        default: return 0;
    }
}

float Channel::evaluateBeforeStartLinear(float t) const {
    const Keyframe & f = getFirstKeyframe();
    return f.getValue() + f.getInTangent() * (t - f.getTime());
}

float Channel::evaluateBeforeStartCycle(float t) const {
    float s = getStartTime(), d = getDuration();
    return evaluate(s + d - fmod((s - t), d));
}

float Channel::evaluateBeforeStartCycleOffset(float t) const {
    float s = getStartTime(), d = getDuration(), o = getValueOffset();
    float tp = s + fmod((s - t), d);
    float off = ceil((s - t) / d) * o;
    return off + evaluate(tp);
}

float Channel::evaluateBeforeStartBounce(float t) const {
    float s = getStartTime(), e = getEndTime(), d = getDuration();
    float tp = fmod((s - t), d) + s;
    int r = (int) floor((s - t) / d);
    if (r % 2) {
        tp = e - (tp - s);
    }
    return evaluate(tp);
}

float Channel::evaluateAfterEndLinear(float t) const {
    const Keyframe & l = getLastKeyframe();
    return l.getValue() + l.getOutTangent() * (t - l.getTime());
}

float Channel::evaluateAfterEndCycle(float t) const {
    float s = getStartTime(), d = getDuration();
    return evaluate(fmod((t - s), d) + s);
}

float Channel::evaluateAfterEndCycleOffset(float t) const {
    float s = getStartTime(), d = getDuration(), o = getValueOffset();
    float tp = fmod((t - s), d) + s;
    float off = floor((t - s) / d) * o;
    return off + evaluate(tp);
}

float Channel::evaluateAfterEndBounce(float t) const {
    float s = getStartTime(), e = getEndTime(), d = getDuration();
    float tp = fmod((t - s), d) + s;
    int r = (int) floor((t - s) / d);
    if (r % 2) {
        tp = d - (tp - s);
    }
    return evaluate(tp);
}

bool Channel::isBeforeStart(float f) const {
    return f < getStartTime();
}

bool Channel::isAfterEnd(float f) const {
    return f > getEndTime();
}

void Channel::setPrevNext(Keyframe & k1, Keyframe & k2) {
    k1.setNext(k2);
    k2.setPrev(k1);
}

void Channel::setCurrPrevNext(Keyframe & p, Keyframe & c, Keyframe & n) {
    setPrevNext(p, c);
    setPrevNext(c, n);
}
