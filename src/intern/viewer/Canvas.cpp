#include "viewer/Canvas.h"

using namespace rotamina;

Canvas::Canvas(Widget *parent) : nanogui::GLCanvas(parent) {
    shader.init();
}

Canvas::~Canvas() {
    shader.free();
}

void Canvas::drawGL() {
    glEnable(GL_DEPTH_TEST);
    shader.bind();
    shader.setUniform("viewPersp", camera.getViewPerspective());
    for (Object * obj : objects) {
        obj->draw(shader);
    }
    glDisable(GL_DEPTH_TEST);
}
