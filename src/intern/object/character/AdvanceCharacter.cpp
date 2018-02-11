#include "object/character/AdvanceCharacter.h"

using namespace rotamina;

AdvanceCharacter::AdvanceCharacter() : Character() {};

Skin & AdvanceCharacter::getSkin() {
    return skin;
}

AdvanceSkin & AdvanceCharacter::getAdvanceSkin() {
    return skin;
}

void AdvanceCharacter::drawSkin(Shader & shader) {
    skin.draw(shader);
}
