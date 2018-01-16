#include "viewer/Viewer.h"

using namespace rotamina;

Viewer::Viewer(int width, int height, std::string name) : nanogui::Screen(Eigen::Vector2i(width, height), name) {
    camera = rotamina::Camera();
    camera.setAspect((float) width / (float) height);
}

Viewer::~Viewer() {
    
}

void Viewer::initiateLayout() {
    // TODO: Initiate Layout
}

void Viewer::draw(NVGcontext * ctx) {
    Screen::draw(ctx);
}

void Viewer::drawContents() {
    Eigen::Matrix4f vp = camera.getViewPerspective();
    for (rotamina::Object * obj : objects) {
        Eigen::Matrix4f model = obj->getTransform();
        Eigen::Matrix4f mvp = model * vp;
        obj->shader.setUniform("ModelMtx", model);
        obj->shader.setUniform("ModelViewProjMtx", mvp);
        obj->draw();
    }
}

rotamina::Camera & Viewer::getCamera() {
    return camera;
}

void Viewer::addObject(rotamina::Object & obj) {
    objects.push_back(&obj);
}

rotamina::Object & Viewer::getObject(int index) {
    return *(objects[index]);
}

void Viewer::createViewer(int width, int height, std::string name, std::function<void(Viewer &)> init) {
    try {
        nanogui::init();
        Viewer viewer = Viewer(width, height, name);
        init(viewer);
        viewer.drawAll();
        viewer.setVisible(true);
        nanogui::mainloop();
        nanogui::shutdown();
    }
    catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
    }
}
