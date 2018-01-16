#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
    private:
        
        
        
    public:
        
        Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
        
        void setEye(glm::vec3 eye);
        void setCenter(glm::vec3 center);
        void setUp(glm::vec3 up);
};

#endif
