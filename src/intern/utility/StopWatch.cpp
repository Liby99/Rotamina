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
    if (isCounting()) {
        d += (std::chrono::system_clock::now() - startTime);
    }
    return d.count();
}

std::string StopWatch::getDurationString() {
    float d = duration();
    int m = floor(d / 60);
    int s = floor(fmod(d, 60));
    int ms = floor(fmod(d, 1) * 1000);
    return padZero(2, m) + " : " + padZero(2, s) + " : " + padZero(3, ms);
}

std::string StopWatch::padZero(int d, int num) {
    std::string s = std::to_string(num);
    while (s.size() < d) {
        s = "0" + s;
    }
    return s;
}