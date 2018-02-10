#ifndef CHARACTER_PARSER_H
#define CHARACTER_PARSER_H

#include "object/skeleton/SkeletonParser.h"
#include "object/skin/SkinParser.h"

class CharacterParser : public Parser {
    public:
        static void loadCharacter(Character & c, const std::string & skelFilename, const std::string & skinFilename);
};

#endif
