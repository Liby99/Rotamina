#ifndef SKELETON_PARSER
#define SKELETON_PARSER

#include <string>
#include <pair>

#include <Eigen/Dense>

#include "utility/Tokenizer.h"

#include "Skeleton.h"
#include "Joint.h"
#include "BallJoint.h"

class SkeletonParser {
    public:
        static Skeleton loadSkeleton(std::string filename);
    private:
        static const int BUF_SIZE = 32;
        static bool loadChildren(Joint & joint, Tokenizer & tokenizer, std::string type);
        static BallJoint loadBallJoint(Tokenizer & tokenizer);
        static Eigen::Vector3f loadVector(Tokenizer & tokenizer);
        static std::pair<float, float> loadMinMax(Tokenizer & tokenizer);
};

#endif
