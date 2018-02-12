#include <iostream>
#include "animation/Channel.h"

using namespace rotamina;

void testExtrapolationConstant() {
    
    Channel t;
    t.addKeyframe(0, 0);
    t.addKeyframe(1, 1);
    t.addKeyframe(3, -1);
    
    std::cout << "at -3: " << t.evaluate(-3) << std::endl;
    std::cout << "at -2.5: " << t.evaluate(-2.5) << std::endl;
    std::cout << "at -2: " << t.evaluate(-2) << std::endl;
    std::cout << "at -1.5: " << t.evaluate(-1.5) << std::endl;
    std::cout << "at -1: " << t.evaluate(-1) << std::endl;
    std::cout << "at -0.5: " << t.evaluate(-0.5) << std::endl;
    std::cout << "at 0: " << t.evaluate(0) << std::endl;
    std::cout << "at 0.5: " << t.evaluate(0.5) << std::endl;
    std::cout << "at 1: " << t.evaluate(1) << std::endl;
    std::cout << "at 1.5: " << t.evaluate(1.5) << std::endl;
    std::cout << "at 2: " << t.evaluate(2) << std::endl;
    std::cout << "at 2.5: " << t.evaluate(2.5) << std::endl;
    std::cout << "at 3: " << t.evaluate(3) << std::endl;
    std::cout << "at 3.5: " << t.evaluate(3.5) << std::endl;
}

int main() {
    testExtrapolationConstant();
}
