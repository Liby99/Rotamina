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
            Keyframe * prev;
            Keyframe * next;
            bool inTangentCached;
            float inTangentCache;
            bool outTangentCached;
            float outTangentCache;
        public:
            Keyframe();
            Keyframe(const float &, const float &);
            void setTime(const float &);
            float getTime() const;
            void setValue(const float &);
            float getValue() const;
            void setConsistent(const bool &);
            bool isConsistent() const;
            void setInTangent(const Tangent &);
            void setInTangent(const float &);
            float getInTangent();
            void setOutTangent(const Tangent &);
            void setOutTangent(const float &);
            float getOutTangent();
            bool hasPrev() const;
            void setPrev(Keyframe &);
            void removePrev();
            Keyframe & getPrev();
            bool hasNext() const;
            void setNext(Keyframe &);
            void removeNext();
            Keyframe & getNext();
            void forceUpdate();
        private:
            float calculateInTangent();
            float calculateOutTangent();
            static float getSlope(const Keyframe &, const Keyframe &);
    };
}

#endif
