#include "object/animator/Animator.h"
#include "utility/StopWatch.h"

using namespace rotamina;

Animator::Animator(Animation & animation) {
    this->animation = &animation;
}

StopWatch & Animator::getStopWatch() {
    return watch;
}

Animation & Animator::getAnimation() {
    return *animation;
}

void Animator::start() {
    watch.start();
}

void Animator::pause() {
    watch.pause();
}

void Animator::stop() {
    watch.stop();
}

bool Animator::isPlaying() {
    return watch.isCounting();
}

float Animator::duration() {
    return watch.duration();
}

void Animator::updateAnimation(float t) {
    // Do nothing. Override this class when inherit
}

void Animator::update() {
    updateAnimation(watch.duration());
}

void Animator::draw(Shader & shader) {
    // Do nothing. Override this class when inherit
}
