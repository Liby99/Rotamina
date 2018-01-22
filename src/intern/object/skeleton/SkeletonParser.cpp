#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

Skeleton SkeletonParser::loadSkeleton(std::string filename) {
    
    Tokenizer tokenizer;
    tokenizer.open(filename, "skel");
    
    Joint * root = new Joint();
    
    char temp[BUF_SIZE];
    tokenizer.getToken(temp);
    
    loadChildren(*root, tokenizer, temp);
    
    Skeleton skel;
    skel.setRoot(*root);
    
    tokenizer.close();
}

bool SkeletonParser::loadChildren(Joint & joint, Tokenizer & tokenizer, std::string type) {
    char temp[BUF_SIZE];
    if (type == "balljoint") {
        BallJoint * bj = loadBallJoint(tokenizer);
        joint.addChildren(*bj);
        return true;
    }
    else {
        return false;
    }
}

BallJoint * SkeletonParser::loadBallJoint(Tokenizer & tokenizer) {
    char temp[BUF_SIZE];
    tokenizer.getToken(temp);
    BallJoint * bj = new BallJoint(std::string(temp));
    tokenizer.findToken("{");
    while (true) {
        tokenizer.getToken(temp);
        if (loadChildren(*bj, tokenizer, temp)) {
            // DO NOTHING
        }
        else if (!strcmp(temp, "offset")) {
            bj->setOffset(loadVector(tokenizer));
        }
        else if (!strcmp(temp, "boxmin")) {
            bj->setBoxMin(loadVector(tokenizer));
        }
        else if (!strcmp(temp, "boxmax")) {
            bj->setBoxMax(loadVector(tokenizer));
        }
        else if (!strcmp(temp, "rotxlimit")) {
            std::pair<float, float> mm = loadMinMax(tokenizer);
            bj->getX().setMinMax(mm.first, mm.second);
        }
        else if (!strcmp(temp, "rotylimit")) {
            std::pair<float, float> mm = loadMinMax(tokenizer);
            bj->getY().setMinMax(mm.first, mm.second);
        }
        else if (!strcmp(temp, "rotzlimit")) {
            std::pair<float, float> mm = loadMinMax(tokenizer);
            bj->getZ().setMinMax(mm.first, mm.second);
        }
        else if (!strcmp(temp, "pose")) {
            bj->setPose(loadVector(tokenizer));
        }
        else if (!strcmp(temp, "}")) {
            return bj;
        }
        else {
            throw std::invalid_argument("Error parsing the file with token [" + std::string(temp) + "]");
        }
    }
}

Eigen::Vector3f SkeletonParser::loadVector(Tokenizer & tokenizer) {
    return Eigen::Vector3f(tokenizer.getFloat(), tokenizer.getFloat(), tokenizer.getFloat());
}

std::pair<float, float> SkeletonParser::loadMinMax(Tokenizer & tokenizer) {
    return std::pair<float, float>(tokenizer.getFloat(), tokenizer.getFloat());
}
