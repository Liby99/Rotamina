#include "object/skin/SkinParser.h"

using namespace rotamina;

void SkinParser::loadSkin(Skin & skin, std::string filename) {
    
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
    }
    
    // Close the file
    tokenizer.close();
}

void SkinParser::loadPositions(Skin & skin, Tokenizer & tokenizer) {
    
    // Setup temp
    char temp[BUF_SIZE];
    
    // Get position amount
    tokenizer.getToken(temp);
    int posAmount = atoi(temp);
    skin.initiateVertices(posAmount);
    
    // Load all the positions
    tokenizer.findToken("{");
    for (int i = 0; i < posAmount; i++) {
        skin.getSkinVertex(i).setPosition(loadVector(tokenizer));
    }
    tokenizer.findToken("}");
}

void SkinParser::loadNormals(Skin & skin, Tokenizer & tokenizer) {
    
    // Setup temp
    char temp[BUF_SIZE];
    
    // Get normal amount
    tokenizer.getToken(temp);
    int normAmount = atoi(temp);
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
    
    // Setup temp
    char temp[BUF_SIZE];
    
    // Get vertex amount
    tokenizer.getToken(temp);
    int vertAmount = atoi(temp);
    skin.initiateVertices(vertAmount);
    
    // Load all skin weights
    tokenizer.findToken("{");
    for (int i = 0; i < vertAmount; i++) {
        
        // Get the attach amount for the current vertex
        tokenizer.getToken(temp);
        int attachAmount = atoi(temp);
        for (int j = 0; j < attachAmount; j++) {
            
            // Add the weight to the vertex
            skin.getSkinVertex(i).addWeight(tokenizer.getInt(), tokenizer.getFloat());
        }
    }
    tokenizer.findToken("}");
}

void SkinParser::loadTriangles(Skin & skin, Tokenizer & tokenizer) {
    
    // Setup temp
    char temp[BUF_SIZE];
    
    // Get triangle amount
    tokenizer.getToken(temp);
    int triAmount = atoi(temp);
    
    // Load the triangles
    tokenizer.findToken("{");
    for (int i = 0; i < triAmount; i++) {
        skin.addTriangle(loadIndices(tokenizer));
    }
    tokenizer.findToken("}");
}

void SkinParser::loadBindings(Skin & skin, Tokenizer & tokenizer) {
    
    // Setup temp
    char temp[BUF_SIZE];
    
    // Get binding matrix amount
    tokenizer.getToken(temp);
    int bindingAmount = atoi(temp);
    
    // Load all binding matrices
    tokenizer.findToken("{");
    for (int i = 0; i < bindingAmount; i++) {
        skin.addInvBinding(loadMatrix34(tokenizer));
    }
    tokenizer.findToken("}");
}
