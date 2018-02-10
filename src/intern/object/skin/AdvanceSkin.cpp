#include "object/skin/AdvanceSkin.h"

using namespace rotamina;

AdvanceSkin::AdvanceSkin() : TexturedSkin(), MorphSkin() {}

void AdvanceSkin::draw(Shader & shader) {
    TexturedSkin::draw(shader);
}
