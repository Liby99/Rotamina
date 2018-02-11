#include <iostream>

class Keyframe {
public:
    enum Tangent { Smooth, Linear, Flat, Custom };
    Tangent in;
    Tangent out;
    Keyframe(Tangent in, Tangent out) : in(in), out(out) {}
};

int main () {
    Keyframe a(Keyframe::Tangent::Smooth, Keyframe::Tangent::Flat);
    std::cout << a.in << " " << a.out << std::endl;
}
