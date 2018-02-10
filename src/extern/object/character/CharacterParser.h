#ifndef CHARACTER_PARSER_H
#define CHARACTER_PARSER_H

#include "object/character/Character.h"
#include "object/skeleton/SkeletonParser.h"
#include "object/skin/SkinParser.h"

namespace rotamina {
    class CharacterParser : public Parser {
        public:
            static void load(Character &, const std::string &, const std::string &);
    };
}

#endif
