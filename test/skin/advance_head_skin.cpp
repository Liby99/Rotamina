#include "viewer/AdvanceCharacterViewer.h"
#include "object/skin/MorphParser.h"
#include "object/character/CharacterParser.h"
#include "object/character/AdvanceCharacter.h"

using namespace rotamina;

int main() {
    
    // First load the character
    AdvanceCharacter c;
    CharacterParser::load(c, "./res/skeletons/head.skel", "./res/skins/head_tex.skin");
    
    // Then load morphs into the skin
    MorphParser::loadMorph(c.getAdvanceSkin(), "./res/morph/head1.morph");
    MorphParser::loadMorph(c.getAdvanceSkin(), "./res/morph/head2.morph");
    
    c.update();
    
    AdvanceCharacterViewer::create(1600, 960, "CSE 169 Project 2 - Head - Morph & Textured", c, [&] (AdvanceCharacterViewer & v) {
    
        // After the viewer is ready, load the texture
        c.getAdvanceSkin().loadTexture("./res/textures/head.bmp");
    });
}
