#include "object/skeleton/DOF.h"

using namespace rotamina;

DOF::DOF() : DOF(-100000, 100000) {}

DOF::DOF(float minValue, float maxValue) : value(0) {
    setMinMax(minValue, maxValue);
}

float DOF::getValue() const {
    return value > maxValue ? maxValue : value < minValue ? minValue : value;
}

float DOF::getMin() const {
    return minValue;
}

float DOF::getMax() const {
    return maxValue;
}

void DOF::setValue(float value) {
    this->value = value;
}

void DOF::setMin(float minValue) {
    this->minValue = minValue;
}

void DOF::setMax(float maxValue) {
    this->maxValue = maxValue;
}

void DOF::setMinMax(float minValue, float maxValue) {
    setMin(minValue);
    setMax(maxValue);
}
