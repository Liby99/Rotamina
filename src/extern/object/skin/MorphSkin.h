#ifndef MORPH_SKIN_H
#define MORPH_SKIN_H

#include "object/skin/TexturedSkin.h"

namespace rotamina {
    class MorphSkin : public TexturedSkin {
        protected:
            std::vector<float> weights;
        public:
            MorphSkin(Skeleton & skel);
            void addWeight();
            void setWeight(int, float);
            std::vector<float> & getWeights();
            float getWeight(int);
        protected:
            virtual void loadPosNorm(Eigen::MatrixXf &, Eigen::MatrixXf &);
    };
}

#endif
