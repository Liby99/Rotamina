#include "object/skin/MorphParser.h"

using namespace rotamina;

void MorphParser::loadMorph(MorphSkin & skin, std::string filename) {

    // Load the file
    Tokenizer tokenizer;
    tokenizer.open(filename.c_str());
    char temp[BUF_SIZE];

    // Mutate the skin
    skin.addWeight();

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
    int totalCounter = 0, totalAmount = skin.skinVertexAmount();
    tokenizer.findToken("{");
    for (int i = 0; i < posAmount; i++) {
        int index = tokenizer.getInt();
        for (int c = totalCounter; c < index; c++) {
            skin.getSkinVertex(c).addMorphPosition();
        }
        totalCounter = index;
        skin.getSkinVertex(index).addMorphPosition(loadVector(tokenizer));
    }
    for (int i = totalCounter; i < totalAmount; i++) {
        skin.getSkinVertex(i).addMorphPosition();
    }
    tokenizer.findToken("}");
}

void MorphParser::loadNormals(MorphSkin & skin, Tokenizer & tokenizer) {
    int normAmount = tokenizer.getInt();
    int totalCounter = 0, totalAmount = skin.skinVertexAmount();
    tokenizer.findToken("{");
    for (int i = 0; i < normAmount; i++) {
        int index = tokenizer.getInt();
        for (int c = totalCounter; c < index; c++) {
            skin.getSkinVertex(c).addMorphNormal();
        }
        totalCounter = index;
        skin.getSkinVertex(index).addMorphNormal(loadVector(tokenizer));
    }
    for (int i = totalCounter; i < totalAmount; i++) {
        skin.getSkinVertex(i).addMorphNormal();
    }
    tokenizer.findToken("}");
}
