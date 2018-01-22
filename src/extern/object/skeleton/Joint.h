#ifndef JOINT_H
#define JOINT_H

#include <vector>
#include <string>
#include <map>

#include <Eigen/Dense>

#include "utility/Tokenizer.h"
#include "object/skeleton/DOF.h"

namespace rotamina {
    
    class Joint {
        protected:
            
            int BUF_SIZE = 32;
            
            std::string name;
            std::map<std::string, DOF *> dofs;
            
            Joint * parent;
            std::vector<rotamina::Joint *> children;
            
        public:
            
            Joint();
            Joint(std::string name);
            
            std::string getName();
            void setName(std::string name);
            std::vector<std::pair<std::string, DOF *>> getDOFs();
            void addChildren(rotamina::Joint * j);
            
            virtual void draw();
            virtual void update(const Eigen::Matrix4f & parentTransf);
    };
}

#endif
