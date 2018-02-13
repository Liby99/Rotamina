#include "object/animator/Animator.h"
#include "utility/StopWatch.h"

using namespace rotamina;

Animator::Animator(Animation & animation) {
    this->animation = &animation;
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

void Animator::updateAnimation(float t) {
    // Do nothing. Override this class when inherit
}

void Animator::update() {
    if (isPlaying()) {
        updateAnimation(watch.duration());
    }
}

void Animator::draw(Shader & shader) {
    // Do nothing. Override this class when inherit
}
