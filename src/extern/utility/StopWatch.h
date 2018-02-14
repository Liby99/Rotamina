#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <chrono>
#include <string>
#include <cmath>

namespace rotamina {
    class StopWatch {
        private:
            bool counting;
            std::chrono::system_clock::time_point startTime;
            std::chrono::duration<float> durationTime;
        public:
            StopWatch();
            bool isCounting();
            void start();
            void pause();
            float stop();
            float duration();
            std::string getDurationString();
        private:
            static std::string padZero(int d, int num);
    };
}

#endif
