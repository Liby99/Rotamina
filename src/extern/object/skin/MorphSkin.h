#ifndef MORPH_SKIN_H
#define MORPH_SKIN_H

#include "object/skin/TexturedSkin.h"

namespace rotamina {
    class MorphSkin : public TexturedSkin {
        protected:
            float perc;
        public:
            MorphSkin(Skeleton & skel);
            void setPercentage(float);
            float getPercentage();
        protected:
            virtual void loadPosNorm(Eigen::MatrixXf &, Eigen::MatrixXf &);
    };
}

#endif
