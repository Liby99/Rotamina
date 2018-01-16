#include "viewer/Viewer.h"

using namespace rotamina;

Viewer * Viewer::app = nullptr;

Viewer::Viewer(int width, int height, std::string name) : nanogui::Screen(Eigen::Vector2i(width, height), name) {
    
    // Setup the camera
    camera = rotamina::Camera();
    
    // Add a default
    objects.push_back(new rotamina::Object());
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
    
    // Eigen::Matrix4f vp;
    // vp.setIdentity();
    // vp.topLeftCorner<3,3>() = Eigen::Matrix3f(Eigen::AngleAxisf((float) glfwGetTime(), Eigen::Vector3f::UnitZ())) * 0.25f;
    
    Eigen::Matrix4f vp = camera.getViewPerspective();
    
    for (rotamina::Object * obj : objects) {
        
        Eigen::Matrix4f model = obj->getTransform();
        Eigen::Matrix4f mvp = model * vp;
        
        obj->shader.setUniform("ModelMtx", model);
        obj->shader.setUniform("ModelViewProjMtx", mvp);
        
        obj->draw();
    }
}

void Viewer::initiate(int width, int height, std::string name, std::function<void(Viewer &)> init) {
    try {
        nanogui::init();
        viewer = new Viewer(width, height, name);
        init(*viewer);
        viewer->drawAll();
        viewer->setVisible(true);
        nanogui::mainloop();
        nanogui::shutdown();
    }
    catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
    }
}
