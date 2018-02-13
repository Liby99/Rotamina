#include <string>
#include <iostream>
#include "animation/Channel.h"

using namespace rotamina;

void error(std::string str) { throw std::runtime_error(str); }
void assert(bool b) { if (!b) { error("Assert Boolean Error"); }}
void assert(float f1, float f2) { if (f1 != f2) { error("Assert Failed - Actual: " + std::to_string(f1) + ", Expected: " + std::to_string(f2)); }}
void assert(int i1, int i2) { if (i1 != i2) { error("Assert Failed - Actual: " + std::to_string(i1) + ", Expected: " + std::to_string(i2)); }}
void print(const std::string & str) { std::cout << str << std::endl; }
void printChannel(Channel & t) {
    std::vector<Keyframe *> ks = t.getKeyframes(); std::cout << "[ ";
    for (int i = 0; i < ks.size(); i++) {
        if (i > 0) std::cout << ", "; std::cout << "(" << ks[i]->getTime() << ": " << ks[i]->getValue() << ")";
    }
    std::cout << " ]" << std::endl;
}
void printChannelInLinkedList(Channel & t) {
    if (t.getKeyframeAmount() == 0) { std::cout << "[]" << std::endl; return; }
    Keyframe k = t.getFirstKeyframe(); std::cout << "[ "; bool flag = false;
    while (true) {
        if (flag) std::cout << ", ";
        std::cout << "(" << k.getTime() << ": " << k.getValue() << ")" << std::flush;
        if (k.hasNext()) { flag = true; k = k.getNext(); }
        else { break; }
    }
    std::cout << " ]" << std::endl;
}

void test1() {
    
    Channel t;
    
    print("-------- Testing Add Keyframes --------");
    
    assert(t.addKeyframe(0, 0));
    assert(t.getKeyframeAmount(), 1);
    assert(t.addKeyframe(1, 1));
    assert(t.getKeyframeAmount(), 2);
    assert(t.addKeyframe(3, -1));
    assert(t.getKeyframeAmount(), 3);
    assert(t.addKeyframe(2, -2));
    assert(t.getKeyframeAmount(), 4);
    
    printChannel(t);
    printChannelInLinkedList(t);
    
    assert(t.getKeyframe(0).getTime(), 0.0f);
    assert(t.getKeyframe(1).getTime(), 1.0f);
    assert(t.getKeyframe(2).getTime(), 2.0f);
    assert(t.getKeyframe(3).getTime(), 3.0f);
    assert(t.getKeyframeAmount(), 4);
    
    assert(!t.addKeyframe(0, 0));
    assert(!t.addKeyframe(1, 0));
    assert(!t.addKeyframe(2, 0));
    assert(!t.addKeyframe(3, 0));
    assert(t.getKeyframeAmount(), 4);
    
    printChannel(t);
    printChannelInLinkedList(t);
    
    assert(t.addKeyframe(0.5, 1.5));
    assert(t.getKeyframeAmount() == 5);
    assert(t.getKeyframe(1).getTime() == 0.5);
    assert(t.getKeyframe(2).getTime() == 1);
    assert(t.getKeyframe(3).getTime() == 2);
    assert(t.addKeyframe(-1, -10));
    assert(t.getKeyframeAmount() == 6);
    assert(t.getKeyframe(0).getTime() == -1);
    assert(t.addKeyframe(50, 3));
    assert(t.getKeyframeAmount() == 7);
    
    printChannel(t);
    printChannelInLinkedList(t);
    
    print("-------- Testing Remove Keyframes --------");
    
    assert(t.removeKeyframe(t.getKeyframe(1)));
    
    printChannelInLinkedList(t);
    
    Keyframe tmp = Keyframe(0.3, 5);
    assert(!t.removeKeyframe(tmp));
    
    printChannelInLinkedList(t);
    
    Keyframe k1 = t.getKeyframe(1);
    assert(t.removeKeyframe(k1));
    
    printChannelInLinkedList(t);
    
    assert(t.removeKeyframe(0));
    assert(t.removeKeyframe(3));
    
    printChannelInLinkedList(t);

    int i = 0;
}

void test2() {
    
}

int main() {
    test1();
    // std::cout << (0.5f == 0.5f) << std::endl;
}
