#include "viewer/CharacterAnimationViewer.h"

using namespace rotamina;

CharacterAnimationViewer::CharacterAnimationViewer(int w, int h, std::string name, CharacterAnimator & ca) : AnimationViewer(w, h, name, ca) {
    this->characterAnimator = &ca;
}
