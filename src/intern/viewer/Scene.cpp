#include "viewer/Scene.h"

using namespace rotamina;

Scene::Scene(Widget *parent) : nanogui::GLCanvas(parent) {
    shader.init();
}

Scene::~Scene() {
    shader.free();
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
        obj->draw(shader);
    }
    glDisable(GL_DEPTH_TEST);
}
