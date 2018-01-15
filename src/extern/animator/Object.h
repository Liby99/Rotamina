#ifndef OBJECT_H

#include <map>
#include <vector>
#include <string>

#include "Animatable.h"

class Object {
    private:
        
        std::map<std::string, Animatable> _fields;
        
    public:
        
        Object();
        
        std::vector<std::string> getKeys();
        
        template<typename T>
        Animatable<T> & get(std::string key);
        
        template<typename T>
        void set(std::string key, const Animatable<T> & value);
};

#endif
