#ifndef ANIMATION_PARSER_H
#define ANIMATION_PARSER_H

#include <string>

#include "utility/Parser.h"
#include "animation/Animation.h"

namespace rotamina {
    class AnimationParser : public Parser {
    public:
        static void load(Animation &, const std::string &);
    private:
        static void loadAnimation(Animation &, Tokenizer &);
        static void loadChannel(Channel &, Tokenizer &);
        static void loadKeyframe(Keyframe &, Tokenizer &);
        static bool getTangent(Tokenizer &, Keyframe::Tangent &, float &);
        static Channel::Extrapolation getExtrapolation(Tokenizer &);
    };
}

#endif
