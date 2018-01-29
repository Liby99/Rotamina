#include "viewer/Canvas.h"

using namespace rotamina;

Canvas::Canvas(Widget *parent) : nanogui::GLCanvas(parent) {
    shader.init();
}

Canvas::~Canvas() {
    shader.free();
}

void Canvas::addObject(rotamina::Object & obj) {
    objects.push_back(&obj);
}

Camera & Canvas::getCamera() {
    return camera;
}

void Canvas::drawGL() {
    glEnable(GL_DEPTH_TEST);
    shader.bind();
    shader.setUniform("viewPersp", camera.getViewPerspective());
    for (rotamina::Object * obj : objects) {
        obj->draw(shader);
    }
    glDisable(GL_DEPTH_TEST);
}
