#include <iostream>
#include "animation/Keyframe.h"

using namespace rotamina;

int main() {
    Keyframe k1, k2;
    k1.setNext(k2);
    k2.setPrev(k1);
    k2.setTime(1);
    k2.setValue(1);
    
    k1.setInTangent(Keyframe::Tangent::Smooth);
    k2.setInTangent(Keyframe::Tangent::Smooth);
    
    std::cout << k1.getOutTangent() << std::endl;
}
