#ifndef SKIN_PARSER_H
#define SKIN_PARSER_H

#include "utility/Parser.h"
#include "object/skin/Skin.h"

namespace rotamina {
    class SkinParser : public Parser {
        public:
            static void loadSkin(Skin & skin, std::string filename);
        private:
            static void loadPositions(Skin & skin, Tokenizer & tokenizer);
            static void loadNormals(Skin & skin, Tokenizer & tokenizer);
            static void loadSkinWeights(Skin & skin, Tokenizer & tokenizer);
            static void loadTriangles(Skin & skin, Tokenizer & tokenizer);
            static void loadBindings(Skin & skin, Tokenizer & tokenizer);
    };
}

#endif
