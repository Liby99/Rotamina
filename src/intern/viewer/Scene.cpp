#include "viewer/Scene.h"

using namespace rotamina;

Scene::Scene(Widget *parent) : nanogui::GLCanvas(parent) {
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

Camera & Scene::getCamera() {
    return camera;
}

void Scene::drawGL() {
    glEnable(GL_DEPTH_TEST);
    shader.bind();
    shader.setUniform("viewPersp", camera.getViewPerspective());
    for (rotamina::Object * obj : objects) {
        obj->update();
        obj->draw(shader);
    }
    glDisable(GL_DEPTH_TEST);
}
