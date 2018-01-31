#include "object/skin/MorphParser.h"

using namespace rotamina;

void MorphParser::loadMorph(MorphSkin & skin, std::string filename) {
    
    // Load the file
    Tokenizer tokenizer;
    tokenizer.open(filename.c_str());
    char temp[BUF_SIZE];
    
    // Go through positions and normals
    while (!tokenizer.isEOF()) {
        tokenizer.getToken(temp);
        if (!strcmp(temp, "positions")) {
            loadPositions(skin, tokenizer);
        }
        else if (!strcmp(temp, "normals")) {
            loadNormals(skin, tokenizer);
        }
    }
    
    // Close the file
    tokenizer.close();
}

void MorphParser::loadPositions(MorphSkin & skin, Tokenizer & tokenizer) {
    int posAmount = tokenizer.getInt();
    tokenizer.findToken("{");
    for (int i = 0; i < posAmount; i++) {
        int index = tokenizer.getInt();
        skin.getSkinVertex(index).setMorphPosition(loadVector(tokenizer));
    }
    tokenizer.findToken("}");
}

void MorphParser::loadNormals(MorphSkin & skin, Tokenizer & tokenizer) {
    int normAmount = tokenizer.getInt();
    tokenizer.findToken("{");
    for (int i = 0; i < normAmount; i++) {
        int index = tokenizer.getInt();
        skin.getSkinVertex(index).setMorphNormal(loadVector(tokenizer));
    }
    tokenizer.findToken("}");
}
