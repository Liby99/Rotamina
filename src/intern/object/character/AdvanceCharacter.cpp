#include "object/character/AdvanceCharacter.h"

using namespace rotamina;

AdvanceCharacter::AdvanceCharacter() : Character() {};

void AdvanceCharacter::drawSkin(Shader & shader) {
    skin.draw(shader);
}
