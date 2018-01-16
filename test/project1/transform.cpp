#include <iostream>
#include <string>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include "utility/Transform.h"

using namespace rotamina;

Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");

void printGlmMat4(glm::mat4 mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    
    // Test1: Transform Counpound transformation
    auto t = Transform();
    t.setPositionX(3);
    t.setPositionY(3);
    t.setPositionZ(5);
    t.setRotationY(M_PI / 2);
    std::cout << t.getTransform().format(CleanFmt) << std::endl;
    
    // Test lookat and glm lookat
    auto myLookAt = Transform::lookAt(Eigen::Vector3f(0, 0, 1), Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(0, 1, 0));
    auto glmLookAt = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    
    std::cout << "My Look At: " << std::endl;
    std::cout << myLookAt.format(CleanFmt) << std::endl;
    
    std::cout << "Glm Look At: " << std::endl;
    printGlmMat4(glmLookAt);
    
    // Test perspective and glm perspective
    float fovy = M_PI / 4.0f;
    float aspect = (float) 1440 / (float) 960;
    float zNear = 0.1f;
    float zFar = 100.0f;
    
    auto myPerspective = Transform::perspective(fovy, aspect, zNear, zFar);
    auto glmPerspective = glm::perspective(fovy, aspect, zNear, zFar);
    
    std::cout << "My Perspective: " << std::endl;
    std::cout << myPerspective.format(CleanFmt) << std::endl;
    
    std::cout << "Glm Perspective: " << std::endl;
    printGlmMat4(glmPerspective);
}
