#include "object/character/CharacterParser.h"

using namespace rotamina;

void CharacterParser::load(Character & c, const std::string & skel, const std::string & skin) {
    SkeletonParser::load(c.getSkeleton(), skel);
    SkinParser::load(c.getSkin(), skin);
}
