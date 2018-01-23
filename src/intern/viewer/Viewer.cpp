#include "viewer/Viewer.h"

using namespace rotamina;

Viewer::Viewer(int width, int height, std::string name) : nanogui::Screen(Eigen::Vector2i(width, height), name) {
    
    this->width = width;
    this->height = height;
    
    camera.setAspect((float) width / (float) height);
}

Viewer::~Viewer() {
    
}

bool Viewer::keyboardEvent(int key, int scancode, int action, int modifiers) {
    // keyboard[key] = (action == GLFW_PRESS);
    return true;
}

bool Viewer::resizeEvent(const Eigen::Vector2i & size) {
    this->width = size[0];
    this->height = size[1];
    camera.setAspect((float) size[0] / (float) size[1]);
    return true;
}

void Viewer::draw(NVGcontext * ctx) {
    Screen::draw(ctx);
}

void Viewer::drawContents() {
    
    // Refresh camera position and get view perspective
    Eigen::Vector3f pos = camera.getPosition();
    pos = Eigen::AngleAxisf((float) glfwGetTime() - prevTime, Eigen::Vector3f(0, 1, 0)) * pos;
    camera.setPosition(pos);
    prevTime = (float) glfwGetTime();
    Eigen::Matrix4f vp = camera.getViewPerspective();
    
    // Draw every object
    for (rotamina::Object * obj : objects) {
        
        obj->shader->bind();
        Eigen::Matrix4f model = obj->transform.getTransform();
        Eigen::Matrix4f mvp = model * vp;
        obj->shader->setUniform("ModelMtx", model);
        obj->shader->setUniform("ModelViewProjMtx", mvp);
        obj->draw();
    }
}

rotamina::Camera & Viewer::getCamera() {
    return camera;
}

void Viewer::addObject(rotamina::Object & obj) {
    objects.push_back(&obj);
}

void Viewer::createViewer(int width, int height, std::string name, std::function<void(Viewer &)> init) {
    try {
        nanogui::init();
        
        // Initiate the viewer
        Viewer viewer = Viewer(width, height, name);
        init(viewer);
        viewer.drawAll();
        viewer.setVisible(true);
        
        // Hack TODO: Find a decent way to enable depth test
        glEnable(GL_DEPTH_TEST);
        
        nanogui::mainloop();
        nanogui::shutdown();
    }
    catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
    }
}
