#ifndef JOINT_H
#define JOINT_H

#include <vector>
#include <string>
#include <map>

#include <Eigen/Dense>

#include "utility/Tokenizer.h"
#include "utility/Shader.h"
#include "utility/Transform.h"
#include "object/skeleton/DOF.h"

namespace rotamina {
    
    class Joint {
        protected:
            
            int BUF_SIZE = 32;
            
            std::string name;
            std::map<std::string, DOF *> dofs;
            Eigen::Matrix4f worldTransf;
            
            Joint * parent;
            std::vector<rotamina::Joint *> children;
            
        public:
            
            Joint();
            Joint(std::string name);
            ~Joint();
            
            std::string getName();
            void setName(std::string name);
            std::vector<std::pair<std::string, DOF *>> getDOFs();
            void addChildren(rotamina::Joint & j);
            std::vector<rotamina::Joint *> getChildren();
            int childrenCount();
            
            virtual std::vector<std::pair<std::string, std::string>> getVars();
            virtual std::string getJointType();
            
            virtual Eigen::Matrix4f getWorldTransform();
            virtual void update(const Eigen::Matrix4f & parentTransf);
            virtual void draw(Shader & shader);
    };
}

#endif
