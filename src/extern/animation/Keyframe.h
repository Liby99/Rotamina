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
            const Keyframe * prev;
            const Keyframe * next;
        public:
            Keyframe();
            void setTime(const float &);
            float getTime() const;
            void setValue(const float &);
            float getValue() const;
            void setConsistent(const bool &);
            bool isConsistent() const;
            void setInTangent(const Tangent &);
            void setInTangent(const float &);
            float getInTangent() const;
            void setOutTangent(const Tangent &);
            void setOutTangent(const float &);
            float getOutTangent() const;
            bool hasPrev() const;
            void setPrev(const Keyframe &);
            const Keyframe & getPrev() const;
            bool hasNext() const;
            void setNext(const Keyframe &);
            const Keyframe & getNext() const;
        private:
            static float getSlope(const Keyframe &, const Keyframe &);
    };
}

#endif
