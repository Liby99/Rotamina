#include "utility/Parser.h"

using namespace rotamina;

Eigen::Vector3i Parser::loadIndices(Tokenizer & tokenizer) {
    return Eigen::Vector3i(tokenizer.getInt(), tokenizer.getInt(), tokenizer.getInt());
}

Eigen::Vector3f Parser::loadVector(Tokenizer & tokenizer) {
    return Eigen::Vector3f(tokenizer.getFloat(), tokenizer.getFloat(), tokenizer.getFloat());
}

Eigen::Matrix4f Parser::loadMatrix34(Tokenizer & tokenizer) {
    tokenizer.findToken("matrix");
    tokenizer.findToken("{");
    Eigen::Matrix4f mat;
    float ax = tokenizer.getFloat(), ay = tokenizer.getFloat(), az = tokenizer.getFloat(),
          bx = tokenizer.getFloat(), by = tokenizer.getFloat(), bz = tokenizer.getFloat(),
          cx = tokenizer.getFloat(), cy = tokenizer.getFloat(), cz = tokenizer.getFloat(),
          dx = tokenizer.getFloat(), dy = tokenizer.getFloat(), dz = tokenizer.getFloat();
    mat << ax, bx, cx, dx,
           ay, by, cy, dy,
           az, bz, cz, dz,
           0,  0,  0,  1;
    tokenizer.findToken("}");
    return mat;
}

std::pair<float, float> Parser::loadMinMax(Tokenizer & tokenizer) {
    return std::make_pair(tokenizer.getFloat(), tokenizer.getFloat());
}
