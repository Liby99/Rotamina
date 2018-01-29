#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include <Eigen/Dense>

#include "utility/Tokenizer.h"

namespace rotamina {
    class Parser {
        protected:
            static const int BUF_SIZE = 32;
            static Eigen::Vector3i loadIndices(Tokenizer & tokenizer);
            static Eigen::Vector3f loadVector(Tokenizer & tokenizer);
            static Eigen::Matrix4f loadMatrix34(Tokenizer & tokenizer);
            static std::pair<float, float> loadMinMax(Tokenizer & tokenizer);
    };
}

#endif
