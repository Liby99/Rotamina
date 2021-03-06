#ifndef SKELETON_PARSER_H
#define SKELETON_PARSER_H

#include "utility/Parser.h"

#include "Skeleton.h"
#include "Joint.h"
#include "BallJoint.h"

namespace rotamina {
    class SkeletonParser : public Parser {
    public:
        static Skeleton load(std::string filename);
        static void load(Skeleton & skel, std::string filename);
    private:
        static bool loadChildren(Skeleton & skel, Joint & joint, Tokenizer & tokenizer, std::string type);
        static Joint * loadJoint(Skeleton & skel, Tokenizer & tokenizer);
        static BallJoint * loadBallJoint(Skeleton & skel, Tokenizer & tokenizer);
    };
}

#endif
