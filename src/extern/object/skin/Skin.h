#ifndef SKIN_H
#define SKIN_H

#include "object/Object.h"
#include "object/skeleton/Skeleton.h"
#include "object/skin/SkinVertex.h"

namespace rotamina {
    class Skin : public Object {
        protected:
            
            bool verticesInitiated;
            
            std::vector<rotamina::SkinVertex> vertices;
            std::vector<Eigen::Vector3i> triangles;
            std::vector<Eigen::Matrix4f> invBindings;
            
        public:
            
            Skin();
            
            void initiateVertices(int);
            int skinVertexAmount();
            SkinVertex & getSkinVertex(int);
            
            int triangleAmount();
            void addTriangle(Eigen::Vector3i);
            
            int bindingMatrixAmount();
            void addInvBinding(Eigen::Matrix4f);
            
            virtual void update(Skeleton & skeleton);
            virtual void draw(rotamina::Shader &);
        
        protected:
            virtual void loadPosNorm(Eigen::MatrixXf &, Eigen::MatrixXf &);
    };
}

#endif
