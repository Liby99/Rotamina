#include "animation/AnimationParser.h"
#include "object/character/CharacterParser.h"
#include "object/animator/CharacterAnimator.h"
#include "viewer/CharAnimViewer.h"

using namespace rotamina;

int main() {
    
    Animation a;
    Character c;
    AnimationParser::load(a, "./res/animations/wasp_walk.anim");
    CharacterParser::load(c, "./res/skeletons/wasp.skel", "./res/skins/wasp.skin");
    CharacterAnimator wa(a, c);

    nanogui::init();
    
    CharAnimViewer viewer(1600, 960, "Wasp Walk Viewer", wa);
    viewer.drawAll();
    viewer.setVisible(true);
    
    nanogui::mainloop();
    nanogui::shutdown();
}
