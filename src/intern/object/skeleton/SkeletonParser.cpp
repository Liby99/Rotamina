#include "object/skeleton/SkeletonParser.h"

using namespace rotamina;

Skeleton SkeletonParser::load(std::string filename) {
    Skeleton skel;
    load(skel, filename);
    return skel;
}

void SkeletonParser::load(Skeleton & skel, std::string filename) {
    
    // Open the file
    Tokenizer tokenizer;
    tokenizer.open(filename.c_str());
    
    // Create joint
    Joint * root = new Joint("Root");
    skel.setRoot(*root);
    
    // DFS load joints
    char temp[BUF_SIZE];
    tokenizer.getToken(temp);
    loadChildren(skel, *root, tokenizer, temp);
    
    // Close the file
    tokenizer.close();
}

bool SkeletonParser::loadChildren(Skeleton & skel, Joint & joint, Tokenizer & tokenizer, std::string type) {
    char temp[BUF_SIZE];
    if (type == "balljoint") {
        BallJoint * bj = loadBallJoint(skel, tokenizer);
        bj->setParent(joint);
        joint.addChildren(*(Joint *)bj);
        return true;
    }
    else if (type == "joint") {
        Joint * j = loadJoint(skel, tokenizer);
        j->setParent(joint);
        joint.addChildren(*j);
        return true;
    }
    else {
        return false;
    }
}

Joint * SkeletonParser::loadJoint(Skeleton & skel, Tokenizer & tokenizer) {
    char temp[BUF_SIZE];
    tokenizer.getToken(temp);
    Joint * j = new Joint(std::string(temp));
    skel.addJoint(*j);
    tokenizer.findToken("{");
    tokenizer.findToken("}");
    return j;
}

BallJoint * SkeletonParser::loadBallJoint(Skeleton & skel, Tokenizer & tokenizer) {
    char temp[BUF_SIZE];
    tokenizer.getToken(temp);
    BallJoint * bj = new BallJoint(std::string(temp));
    skel.addJoint(*(Joint *)bj);
    tokenizer.findToken("{");
    while (true) {
        tokenizer.getToken(temp);
        if (loadChildren(skel, *bj, tokenizer, temp)) {
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
