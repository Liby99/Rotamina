#include "object/skeleton/DOF.h"

using namespace rotamina;

DOF::DOF(float minValue, float maxValue) : value(0) {
    setMinMax(minValue, maxValue);
}

float DOF::getValue() {
    return value > maxValue ? maxValue : value < minValue ? minValue : value;
}

float DOF::getMin() {
    return minValue;
}

float DOF::getMax() {
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
