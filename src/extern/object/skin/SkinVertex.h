#ifndef SKIN_VERTEX_H
#define SKIN_VERTEX_H

#include <vector>
#include <utility>
#include <Eigen/Dense>

namespace rotamina {
    class SkinVertex {
        private:
            
            Eigen::Vector3f currPos;
            Eigen::Vector3f currNorm;
            Eigen::Vector3f currMorphPos;
            Eigen::Vector3f currMorphNorm;
            
            Eigen::Vector3f position;
            Eigen::Vector3f normal;
            Eigen::Vector2f texCoord;
            std::vector<std::pair<int, float>> weights;
            
            Eigen::Vector3f morphPosition;
            Eigen::Vector3f morphNormal;
            
        public:
            
            SkinVertex();
            
            void setPosition(Eigen::Vector3f);
            void setNormal(Eigen::Vector3f);
            void setTexCoord(Eigen::Vector2f);
            void addWeight(int, float);
            
            void setMorphPosition(Eigen::Vector3f);
            void setMorphNormal(Eigen::Vector3f);
            
            Eigen::Vector3f getPosition(float);
            Eigen::Vector3f getPosition();
            Eigen::Vector3f getNormal(float);
            Eigen::Vector3f getNormal();
            Eigen::Vector2f getTexCoord();
            std::pair<int, float> & getWeight(int i);
            std::vector<std::pair<int, float>> & getWeights();
            
            void update(std::vector<Eigen::Matrix4f> & matrices);
    };
}

#endif
