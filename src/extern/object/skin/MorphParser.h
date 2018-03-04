#ifndef MORPH_PARSER_H
#define MORPH_PARSER_H

#include "utility/Parser.h"
#include "object/skin/MorphSkin.h"

namespace rotamina {
    class MorphParser : public Parser {
    public:
        static void loadMorph(MorphSkin & skin, std::string filename);
    public:
        static void loadPositions(MorphSkin & skin, Tokenizer & tokenizer);
        static void loadNormals(MorphSkin & skin, Tokenizer & tokenizer);
    };
}

#endif
