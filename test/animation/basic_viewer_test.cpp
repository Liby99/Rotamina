#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    
    // Initiate
    Animation a;
    Character c;
    
    // Load
    AnimationParser::load(a, "./res/animations/wasp_walk.anim");
    CharacterParser::load(c, "./res/skeletons/wasp.skel", "./res/skins/wasp.skin");
    
    // Add to Animator
    CharacterAnimator waspAnimator(a, c);
    
    AnimationViewer::create(1280, 720, "Wasp Walk Viewer", waspAnimator, [&](AnimationViewer &v) {
        
    });
}
