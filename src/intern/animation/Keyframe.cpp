#include "animation/Keyframe.h"

using namespace rotamina;

Keyframe::Keyframe() : Keyframe(0, 0) {}
    
Keyframe::Keyframe(const float & t, const float & v) : time(t), value(v), consistent(true),
    in(Tangent::Linear), out(Tangent::Linear), inSlope(0), outSlope(0), prev(nullptr), next(nullptr) {}

void Keyframe::setTime(const float & t) {
    this->time = t;
}

float Keyframe::getTime() const {
    return this->time;
}

void Keyframe::setValue(const float & v) {
    this->value = v;
}

float Keyframe::getValue() const {
    return this->value;
}

void Keyframe::setConsistent(const bool & c) {
    this->consistent = c;
}

bool Keyframe::isConsistent() const {
    return this->consistent;
}

void Keyframe::setInTangent(const Tangent & in) {
    this->in = in;
    if (isConsistent()) {
        this->out = in;
    }
}

void Keyframe::setInTangent(const float & s) {
    this->in = Tangent::Custom;
    this->inSlope = s;
    if (isConsistent()) {
        this->out = Tangent::Custom;
        this->outSlope = s;
    }
}

float Keyframe::getInTangent() const {
    switch (in) {
        case Tangent::Smooth: {
            if (prev && next) return getSlope(*next, *prev);
            else if (prev) return getSlope(*this, *prev);
            else return 0;
        }; break;
        case Tangent::Linear: {
            if (prev) return getSlope(*this, *prev);
            else return 0;
        }; break;
        case Tangent::Flat: {
            return 0;
        }; break;
        case Tangent::Custom: {
            return inSlope;
        }; break;
    }
}

void Keyframe::setOutTangent(const Tangent & out) {
    this->out = out;
    if (isConsistent()) {
        this->in = out;
    }
}

void Keyframe::setOutTangent(const float & s) {
    this->out = Tangent::Custom;
    this->outSlope = s;
    if (isConsistent()) {
        this->in = Tangent::Custom;
        this->outSlope = s;
    }
}

float Keyframe::getOutTangent() const {
    switch (out) {
        case Tangent::Smooth: {
            if (prev && next) return getSlope(*next, *prev);
            else if (next) return getSlope(*next, *this);
            else return 0;
        }; break;
        case Tangent::Linear: {
            if (next) return getSlope(*this, *next);
            else return 0;
        }; break;
        case Tangent::Flat: {
            return 0;
        }; break;
        case Tangent::Custom: {
            return inSlope;
        }; break;
    }
}

bool Keyframe::hasPrev() const {
    return prev != nullptr;
}

void Keyframe::setPrev(Keyframe & k) {
    this->prev = &k;
}

void Keyframe::removePrev() {
    this->prev = nullptr;
}

Keyframe & Keyframe::getPrev() {
    return *prev;
}

bool Keyframe::hasNext() const {
    return next != nullptr;
}

void Keyframe::setNext(Keyframe & k) {
    this->next = &k;
}

void Keyframe::removeNext() {
    this->next = nullptr;
}

Keyframe & Keyframe::getNext() {
    return *next;
}

float Keyframe::getSlope(const Keyframe & k1, const Keyframe & k2) {
    return (k2.value - k1.value) / (k2.time - k1.time);
}
