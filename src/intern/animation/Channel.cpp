#include <iostream>
#include "animation/Channel.h"

using namespace rotamina;

Channel::Channel() : in(Extrapolation::Constant), out(Extrapolation::Constant), initiated(false) {}

Channel::~Channel() {
    for (int i = 0; i < keyframes.size(); i++) {
        delete keyframes[i];
    }
}

void Channel::initiateKeyframes(const int & amount) {
    if (!initiated) {
        for (int i = 0; i < amount; i++) {
            keyframes.push_back(new Keyframe());
            if (i != 0) {
                setPrevNext(keyframes[i - 1], keyframes[i]);
            }
        }
        initiated = true;
    }
}

bool Channel::addKeyframe(const float & t, const float & v) {
    if (keyframes.size() == 0) {
        keyframes.push_back(new Keyframe(t, v));
    }
    else if (keyframes.size() == 1) {
        if (t == keyframes[0]->getTime()) {
            return false;
        }
        else if (t > keyframes[0]->getTime()) {
            keyframes.push_back(new Keyframe(t, v));
        }
        else {
            keyframes.insert(keyframes.begin(), new Keyframe(t, v));
        }
        setPrevNext(keyframes[0], keyframes[1]);
    }
    else {
        if (t < keyframes[0]->getTime()) {
            keyframes.insert(keyframes.begin(), new Keyframe(t, v));
            setPrevNext(keyframes[0], keyframes[1]);
        }
        else if (t > keyframes[keyframes.size() - 1]->getTime()) {
            keyframes.push_back(new Keyframe(t, v));
            setPrevNext(keyframes[keyframes.size() - 2], keyframes[keyframes.size() - 1]);
        }
        else {
            int s = 0, e = keyframes.size(), m = 0;
            while (s < e - 1) {
                m = (s + e) / 2;
                float kt = keyframes[m]->getTime();
                if (t > kt) {
                    s = m;
                }
                else if (t == kt) {
                    return false;
                }
                else {
                    e = m;
                }
            }
            if (keyframes[s]->getTime() == t || keyframes[e]->getTime() == t) {
                return false;
            }
            keyframes.insert(keyframes.begin() + s + 1, new Keyframe(t, v));
            setCurrPrevNext(keyframes[s], keyframes[s + 1], keyframes[s + 2]);
        }
    }
    return true;
}

bool Channel::removeKeyframe(int i) {
    int l = keyframes.size();
    if (i < 0 || i >= l) {
        return false;
    }
    else if (l == 1) {
        delete keyframes[0];
        keyframes.erase(keyframes.begin());
    }
    else {
        delete keyframes[i];
        if (i == 0) {
            keyframes.erase(keyframes.begin());
            keyframes[0]->removePrev();
        }
        else if (i == l - 1) {
            keyframes.erase(keyframes.end() - 1);
            keyframes[keyframes.size() - 1]->removeNext();
        }
        else {
            setPrevNext(keyframes[i - 1], keyframes[i + 1]);
            keyframes.erase(keyframes.begin() + i);
        }
    }
    return true;
}

bool Channel::removeKeyframe(Keyframe & k) {
    int s = 0, e = keyframes.size(), m = 0;
    float tt = k.getTime();
    while (s < e) {
        m = (s + e) / 2;
        float mt = keyframes[m]->getTime();
        if (mt == tt) {
            return removeKeyframe(m);
        }
        else if (mt > tt) {
            e = m - 1;
        }
        else {
            s = m + 1;
        }
    }
    if (keyframes[s]->getTime() != tt) {
        return false;
    }
    else {
        return removeKeyframe(s);
    }
}

std::vector<Keyframe *> & Channel::getKeyframes() {
    return keyframes;
}

int Channel::getKeyframeAmount() const {
    return keyframes.size();
}

Keyframe & Channel::getFirstKeyframe() {
    return *keyframes[0];
}

Keyframe & Channel::getKeyframe(int i) {
    return *keyframes[i];
}

Keyframe & Channel::getLastKeyframe() {
    return *keyframes[keyframes.size() - 1];
}

float Channel::getStartTime() const {
    return keyframes[0]->getTime();
}

float Channel::getEndTime() const {
    return keyframes[keyframes.size() - 1]->getTime();
}

float Channel::getDuration() const {
    return getEndTime() - getStartTime();
}

float Channel::getStartValue() const {
    return keyframes[0]->getValue();
}

float Channel::getEndValue() const {
    return keyframes[keyframes.size() - 1]->getValue();
}

float Channel::getValueOffset() const {
    return keyframes[keyframes.size() - 1]->getValue() - keyframes[0]->getValue();
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
    switch (getKeyframeAmount()) {
        case 0: {
            return 0;
        }
        case 1: {
            return keyframes[0]->getValue();
        }
        default: {
            if (isBeforeStart(t)) {
                return evaluateBeforeStart(t);
            }
            else if (isAfterEnd(t)) {
                return evaluateAfterEnd(t);
            }
            else {
                int s = 0, e = keyframes.size(), m = 0;
                while (s < e - 1) {
                    m = (s + e) / 2;
                    float kt = keyframes[m]->getTime();
                    if (t > kt) {
                        s = m;
                    }
                    else if (t == kt) {
                        return keyframes[m]->getValue();
                    }
                    else {
                        e = m;
                    }
                }
                if (keyframes[s]->getTime() == t) {
                    return keyframes[s]->getValue();
                }
                else if (keyframes[e]->getTime() == t) {
                    return keyframes[e]->getValue();
                }
                else {
                    return interpolate(keyframes[s], keyframes[e], t);
                }
            }
        }
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
    Keyframe * f = keyframes[0];
    return f->getValue() + f->getInTangent() * (t - f->getTime());
}

float Channel::evaluateBeforeStartCycle(float t) const {
    float s = getStartTime(), d = getDuration();
    return evaluate(s + d - fmod((s - t), d));
}

float Channel::evaluateBeforeStartCycleOffset(float t) const {
    float s = getStartTime(), d = getDuration(), o = getValueOffset();
    float tp = s + (d - fmod((s - t), d));
    float off = ceil((s - t) / d) * o;
    return -off + evaluate(tp);
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
    Keyframe * l = keyframes[keyframes.size() - 1];
    return l->getValue() + l->getOutTangent() * (t - l->getTime());
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
        tp = e - (tp - s);
    }
    return evaluate(tp);
}

bool Channel::isBeforeStart(float f) const {
    return f < getStartTime();
}

bool Channel::isAfterEnd(float f) const {
    return f > getEndTime();
}

float Channel::interpolate(Keyframe * k0, Keyframe * k1, float gt) {
    float dur = k1->getTime() - k0->getTime(),
          p0 = k0->getValue(), p1 = k1->getValue(),
          v0 = dur * k0->getOutTangent(), v1 = dur * k1->getInTangent(),
          a = 2 * p0 - 2 * p1 + v0 + v1,
          b = -3 * p0 + 3 * p1 - 2 * v0 - v1;
    float t = (gt - k0->getTime()) / dur;
    return ((a * t + b) * t + v0) * t + p0;
}

void Channel::setPrevNext(Keyframe * k1, Keyframe * k2) {
    k1->setNext(*k2);
    k2->setPrev(*k1);
}

void Channel::setCurrPrevNext(Keyframe * p, Keyframe * c, Keyframe * n) {
    setPrevNext(p, c);
    setPrevNext(c, n);
}
