#include <string>
#include <iostream>
#include "animation/AnimationParser.h"

using namespace rotamina;

int main() {
    Animation a;
    AnimationParser::load(a, "./res/animations/wasp_walk.anim");

    Channel & c = a.getChannel(3 + 11 * 3 + 1);

    float d = 0, y = 0;

    for (float f = 0; f <= 4; f += 0.1) {
        float ny = c.evaluate(f);
        d = ny - y;
        y = ny;
        std::cout << "(" << f << ": " << ny << ")" << ", d: " << d << std::endl;
    }
}