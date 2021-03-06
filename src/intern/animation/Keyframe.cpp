#include "animation/Keyframe.h"

using namespace rotamina;

Keyframe::Keyframe() : Keyframe(0, 0) {}
    
Keyframe::Keyframe(const float & t, const float & v) :
    time(t), value(v),
    consistent(true), inTangentCached(false),
    in(Tangent::Flat), out(Tangent::Flat), inSlope(0), outSlope(0),
    prev(nullptr), next(nullptr) {}

void Keyframe::setTime(const float & t) {
    this->time = t;
    this->forceUpdate();
    if (this->prev) this->prev->forceUpdate();
    if (this->next) this->next->forceUpdate();
}

float Keyframe::getTime() const {
    return this->time;
}

void Keyframe::setValue(const float & v) {
    this->value = v;
    this->forceUpdate();
    if (this->prev) this->prev->forceUpdate();
    if (this->next) this->next->forceUpdate();
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
    inTangentCached = false;
}

void Keyframe::setInTangent(const float & s) {
    this->in = Tangent::Custom;
    this->inSlope = s;
    if (isConsistent()) {
        this->out = Tangent::Custom;
        this->outSlope = s;
    }
    inTangentCached = false;
}

float Keyframe::getInTangent() {
    if (!inTangentCached) {
        this->inTangentCache = calculateInTangent();
        this->inTangentCached = true;
    }
    return this->inTangentCache;
}

void Keyframe::setOutTangent(const Tangent & out) {
    this->out = out;
    if (isConsistent()) {
        this->in = out;
    }
    outTangentCached = false;
}

void Keyframe::setOutTangent(const float & s) {
    this->out = Tangent::Custom;
    this->outSlope = s;
    if (isConsistent()) {
        this->in = Tangent::Custom;
        this->outSlope = s;
    }
    outTangentCached = false;
}

float Keyframe::getOutTangent() {
    if (!outTangentCached) {
        this->outTangentCache = calculateOutTangent();
        this->outTangentCached = true;
    }
    return this->outTangentCache;
}

bool Keyframe::hasPrev() const {
    return prev != nullptr;
}

void Keyframe::setPrev(Keyframe & k) {
    this->prev = &k;
    this->forceUpdate();
    if (this->prev) this->prev->forceUpdate();
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
    this->forceUpdate();
    if (this->next) this->next->forceUpdate();
}

void Keyframe::removeNext() {
    this->next = nullptr;
}

Keyframe & Keyframe::getNext() {
    return *next;
}

void Keyframe::forceUpdate() {
    this->inTangentCached = false;
    this->outTangentCached = false;
}

float Keyframe::calculateInTangent() {
    switch (in) {
        case Tangent::Smooth:
            if (prev && next) return getSlope(*prev, *next);
            else if (prev) return getSlope(*prev, *this);
            else if (next) return getSlope(*this, *next);
            else return 0;
        case Tangent::Linear:
            if (prev) return getSlope(*prev, *this);
            else if (next) return getSlope(*this, *next);
            else return 0;
        case Tangent::Flat:
            return 0;
        case Tangent::Custom:
            return inSlope;
    }
}

float Keyframe::calculateOutTangent() {
    switch (out) {
        case Tangent::Smooth:
            if (prev && next) return getSlope(*prev, *next);
            else if (next) return getSlope(*this, *next);
            else if (prev) return getSlope(*prev, *this);
            else return 0;
        case Tangent::Linear:
            if (next) return getSlope(*this, *next);
            else if (prev) return getSlope(*prev, *this);
            else return 0;
        case Tangent::Flat:
            return 0;
        case Tangent::Custom:
            return outSlope;
    }
}

float Keyframe::getSlope(const Keyframe & k1, const Keyframe & k2) {
    return (k2.value - k1.value) / (k2.time - k1.time);
}
