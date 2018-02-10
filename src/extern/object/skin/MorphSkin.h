#ifndef MORPH_SKIN_H
#define MORPH_SKIN_H

#include "object/skin/Skin.h"

namespace rotamina {
    class MorphSkin : public Skin {
        protected:
            std::vector<float> weights;
        public:
            MorphSkin();
            void addWeight();
            void setWeight(int, float);
            std::vector<float> & getWeights();
            float getWeight(int);
        protected:
            virtual void loadPosNorm(Eigen::MatrixXf &, Eigen::MatrixXf &);
    };
}

#endif
