#include <iostream>
#include <vector>
#include <rotamina/rotamina.h>

using namespace rotamina;

int main () {
    Character c;
    CharacterParser::load(c, "./res/skeletons/tube.skel", "./res/skins/tube_smooth.skin");
    c.update();
}
