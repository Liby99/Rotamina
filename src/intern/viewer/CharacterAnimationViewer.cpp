#include "viewer/CharacterAnimationViewer.h"

using namespace rotamina;

CharacterAnimationViewer::CharacterAnimationViewer(int w, int h, std::string n, CharacterAnimator & ca) : AnimationViewer(w, h, n, ca) {
    this->characterAnimator = &ca;
    
    using namespace nanogui;
    
    
}
