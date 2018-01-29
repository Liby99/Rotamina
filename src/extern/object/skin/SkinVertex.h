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
            
            Eigen::Vector3f position;
            Eigen::Vector3f normal;
            Eigen::Vector2f texCoord;
            std::vector<std::pair<int, float>> weights;
            
        public:
            
            SkinVertex();
            
            void setPosition(Eigen::Vector3f);
            void setNormal(Eigen::Vector3f);
            void setTexCoord(Eigen::Vector2f);
            void addWeight(int, float);
            
            Eigen::Vector3f getPosition();
            Eigen::Vector3f getNormal();
            Eigen::Vector2f getTexCoord();
            std::pair<int, float> & getWeight(int i);
            std::vector<std::pair<int, float>> & getWeights();
            
            void update(std::vector<Eigen::Matrix4f> & matrices);
    };
}

#endif
