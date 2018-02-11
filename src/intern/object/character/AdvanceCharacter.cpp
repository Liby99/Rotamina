#include "object/character/AdvanceCharacter.h"

using namespace rotamina;

AdvanceCharacter::AdvanceCharacter() : Character() {};

AdvanceSkin & AdvanceCharacter::getSkin() {
    return skin;
}

void AdvanceCharacter::drawSkin(Shader & shader) {
    skin.draw(shader);
}
