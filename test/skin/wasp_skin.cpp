#include <iostream>
#include <vector>

#include "viewer/CharacterViewer.h"
#include "object/character/CharacterParser.h"

using namespace rotamina;

int main () {
    
    // Initiate skel and skin
    Character c;
    CharacterParser::load(c, "../res/skeletons/wasp.skel", "../res/skins/wasp.skin");
    
    // Create the viewer
    CharacterViewer::create(1600, 960, "CSE 169 Project 2 - Wasp", c, [&] (CharacterViewer & v) {});
}
