#include "object/skin/SkinParser.h"

using namespace rotamina;

void SkinParser::load(Skin & skin, std::string filename) {
    
    // Load the file
    Tokenizer tokenizer;
    tokenizer.open(filename.c_str());
    char temp[BUF_SIZE];
    
    // Read the data of the file
    while (!tokenizer.isEOF()) {
        tokenizer.getToken(temp);
        if (!strcmp(temp, "positions")) {
            loadPositions(skin, tokenizer);
        }
        else if (!strcmp(temp, "normals")) {
            loadNormals(skin, tokenizer);
        }
        else if (!strcmp(temp, "skinweights")) {
            loadSkinWeights(skin, tokenizer);
        }
        else if (!strcmp(temp, "triangles")) {
            loadTriangles(skin, tokenizer);
        }
        else if (!strcmp(temp, "bindings")) {
            loadBindings(skin, tokenizer);
        }
        else if (!strcmp(temp, "texcoords")) {
            loadTexCoords(skin, tokenizer);
        }
    }
    
    // Close the file
    tokenizer.close();
}

void SkinParser::loadPositions(Skin & skin, Tokenizer & tokenizer) {
    
    // Get position amount
    int posAmount = tokenizer.getInt();
    skin.initiateVertices(posAmount);
    
    // Load all the positions
    tokenizer.findToken("{");
    for (int i = 0; i < posAmount; i++) {
        skin.getSkinVertex(i).setPosition(loadVector(tokenizer));
    }
    tokenizer.findToken("}");
}

void SkinParser::loadNormals(Skin & skin, Tokenizer & tokenizer) {
    
    // Get normal amount
    int normAmount = tokenizer.getInt();
    skin.initiateVertices(normAmount);
    
    // Load all normals
    tokenizer.findToken("{");
    for (int i = 0; i < normAmount; i++) {
        Eigen::Vector3f norm = loadVector(tokenizer);
        norm.normalize();
        skin.getSkinVertex(i).setNormal(norm);
    }
    tokenizer.findToken("}");
}

void SkinParser::loadSkinWeights(Skin & skin, Tokenizer & tokenizer) {
    
    // Get vertex amount
    int vertAmount = tokenizer.getInt();
    skin.initiateVertices(vertAmount);
    
    // Load all skin weights
    tokenizer.findToken("{");
    for (int i = 0; i < vertAmount; i++) {
        
        // Get the attach amount for the current vertex
        int attachAmount = tokenizer.getInt();
        for (int j = 0; j < attachAmount; j++) {
            
            // Add the weight to the vertex
            skin.getSkinVertex(i).addWeight(tokenizer.getInt(), tokenizer.getFloat());
        }
    }
    tokenizer.findToken("}");
}

void SkinParser::loadTriangles(Skin & skin, Tokenizer & tokenizer) {
    int triAmount = tokenizer.getInt();
    tokenizer.findToken("{");
    for (int i = 0; i < triAmount; i++) {
        skin.addTriangle(loadIndices(tokenizer));
    }
    tokenizer.findToken("}");
}

void SkinParser::loadBindings(Skin & skin, Tokenizer & tokenizer) {
    int bindingAmount = tokenizer.getInt();
    tokenizer.findToken("{");
    for (int i = 0; i < bindingAmount; i++) {
        skin.addInvBinding(loadMatrix34(tokenizer));
    }
    tokenizer.findToken("}");
}

void SkinParser::loadTexCoords(Skin & skin, Tokenizer & tokenizer) {
    int texAmount = tokenizer.getInt();
    tokenizer.findToken("{");
    for (int i = 0; i < texAmount; i++) {
        skin.getSkinVertex(i).setTexCoord(loadVector2f(tokenizer));
    }
    tokenizer.findToken("}");
}
