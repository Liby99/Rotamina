#ifndef KEYFRAME_H
#define KEYFRAME_H

namespace rotamina {
    class Keyframe {
        public:
            enum Tangent { Flat, Linear, Smooth, Custom };
        protected:
            float time;
            float value;
            Tangent in;
            Tangent out;
            float inSlope;
            float outSlope;
            bool consistent;
        public:
            Keyframe();
            void setTime(float);
            float getTime();
            void setValue(float);
            float getValue();
            void setConsistent(bool);
            bool isConsistent();
            void setInTangent(Tangent in);
            void setInTangent(float slope);
            void setOutTangent(Tangent in);
            void setOutTangent(float slope);
            float getInTangent();
            float getOutTangent();
    };
}

#endif
