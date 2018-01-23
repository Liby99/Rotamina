#ifndef DOF_H
#define DOF_H

namespace rotamina {
    class DOF {
        private:
            float minValue;
            float maxValue;
            float value;
        public:
            DOF();
            DOF(float minValue, float maxValue);
            float getValue() const;
            float getMin() const;
            float getMax() const;
            void setValue(float value);
            void setMin(float minValue);
            void setMax(float maxValue);
            void setMinMax(float minValue, float maxValue);
    };
}

#endif
