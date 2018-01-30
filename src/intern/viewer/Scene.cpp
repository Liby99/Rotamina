#include "viewer/Scene.h"

using namespace rotamina;

const float Scene::SCROLL_SPEED = 0.1f;
const float Scene::MOVE_SPEED = 0.004f;

Scene::Scene(Widget *parent) : nanogui::GLCanvas(parent) {
    azimuth = 0;
    incline = 0;
    dist = 3;
    shader.init();
}

Scene::~Scene() {
    shader.free();
}

void Scene::setSize(int width, int height) {
    GLCanvas::setSize({ width, height });
    camera.setSize(width, height);
}

void Scene::setWidth(int width) {
    GLCanvas::setWidth(width);
    camera.setWidth(width);
}

void Scene::setHeight(int height) {
    GLCanvas::setHeight(height);
    camera.setHeight(height);
}

int Scene::getWidth() {
    return camera.getWidth();
}

int Scene::getHeight() {
    return camera.getHeight();
}

void Scene::addObject(rotamina::Object & obj) {
    objects.push_back(&obj);
}

bool Scene::removeObject(int i) {
    if (objects.size() <= i) {
        return false;
    }
    objects.erase(objects.begin() + i);
    return true;
}

unsigned int Scene::objectCount() {
    return objects.size();
}

Camera & Scene::getCamera() {
    return camera;
}

void Scene::updateCamera() {
    using namespace Eigen;
    
    Vector3f pos = Vector3f(0, 0, dist);
    Matrix3f m;
    m = AngleAxisf(azimuth, Vector3f::UnitY()) * AngleAxisf(incline, Vector3f::UnitX());
    
    camera.setPosition(m * pos);
}

Shader & Scene::getShader() {
    return shader;
}

bool Scene::keyboardEvent(int key, int scancode, int action, int modifiers) {
    return true;
}

bool Scene::mouseDragEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) {
    azimuth -= rel[0] * MOVE_SPEED;
    incline = fmaxf(-M_PI / 2 + 0.01f, fminf(M_PI / 2 - 0.01f, incline - rel[1] * MOVE_SPEED));
    return true;
}

bool Scene::mouseMotionEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) {
    return true;
}

bool Scene::scrollEvent(const Eigen::Vector2i & p, const Eigen::Vector2f & rel) {
    dist = fmaxf(0.01f, dist - rel[1] * SCROLL_SPEED);
    return true;
}

void Scene::drawGL() {
    glEnable(GL_DEPTH_TEST);
    
    // Update camera related info
    updateCamera();
    shader.bind();
    shader.setUniform("viewPersp", camera.getViewPerspective());
    
    // Draw all the objects
    for (rotamina::Object * obj : objects) {
        obj->update();
        if (!obj->isHidden()) {
            obj->draw(shader);
        }
    }
    
    glDisable(GL_DEPTH_TEST);
}
