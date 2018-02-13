#include "utility/StopWatch.h"

using namespace rotamina;

StopWatch::StopWatch() : counting(false) {
    durationTime = std::chrono::duration<float>::zero();
}

bool StopWatch::isCounting() {
    return counting;
}

void StopWatch::start() {
    counting = true;
    startTime = std::chrono::system_clock::now();
}

void StopWatch::pause() {
    if (counting) {
        counting = false;
        durationTime += std::chrono::system_clock::now() - startTime;
    }
}

float StopWatch::stop() {
    pause();
    float result = durationTime.count();
    counting = false;
    durationTime = std::chrono::duration<float>::zero();
    return result;
}

float StopWatch::duration() {
    auto d = durationTime;
    d += (std::chrono::system_clock::now() - startTime);
    return d.count();
}
