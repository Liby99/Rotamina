#include <iostream>
#include <vector>

#include "viewer/CharacterViewer.h"
#include "object/character/CharacterParser.h"

using namespace rotamina;

int main () {
    
    // Initiate skel and skin
    Character c;
    CharacterParser::load(c, "./res/skeletons/head.skel", "./res/skins/head_tex.skin");
    
    // Create the viewer
    CharacterViewer::create(1600, 960, "CSE 169 Project 2 - Head", c, [&] (CharacterViewer & v) {});
}
