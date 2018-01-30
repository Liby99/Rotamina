#ifndef SKELETON_PARSER_H
#define SKELETON_PARSER_H

#include "utility/Parser.h"

#include "Skeleton.h"
#include "Joint.h"
#include "BallJoint.h"

namespace rotamina {
    class SkeletonParser : public Parser {
        public:
            static Skeleton loadSkeleton(std::string filename);
            static void loadSkeleton(Skeleton & skel, std::string filename);
        private:
            static bool loadChildren(Skeleton & skel, Joint & joint, Tokenizer & tokenizer, std::string type);
            static BallJoint * loadBallJoint(Skeleton & skel, Tokenizer & tokenizer);
    };
}

#endif
