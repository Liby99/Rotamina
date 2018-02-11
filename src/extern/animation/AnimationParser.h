#ifndef ANIMATION_PARSER_H
#define ANIMATION_PARSER_H

#include <string>

#include "animation/Animation.h"

namespace rotamina {
    class AnimationParser {
        public:
            static void load(Animation &, const std::string & filename);
    };
}

#endif
