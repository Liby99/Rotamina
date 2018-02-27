#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    
    // First load the character
    AdvanceCharacter c;
    CharacterParser::load(c, "./res/skeletons/head.skel", "./res/skins/head_tex.skin");
    
    // Then load morphs into the skin
    MorphParser::loadMorph(c.getSkin(), "./res/morphs/head1.morph");
    MorphParser::loadMorph(c.getSkin(), "./res/morphs/head2.morph");
    
    c.update();
    
    AdvanceCharacterViewer::create(1600, 960, "CSE 169 Project 2 - Head - Morph & Textured", c, [&] (AdvanceCharacterViewer & v) {
    
        // After the viewer is ready, load the texture
        c.getSkin().loadTexture("./res/textures/head.bmp");
    });
}
