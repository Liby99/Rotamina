#include "viewer/Viewer.h"

using namespace rotamina;

const nanogui::Color Viewer::BACKGROUND = { 30, 30, 30, 255 };
const int Viewer::HEADER_HEIGHT = 28;
const int Viewer::PADDING = 5;

Viewer::Viewer(int w, int h, std::string name) : nanogui::Screen(Eigen::Vector2i(w, h), name, false) {
    
    using namespace nanogui;
    
    // Set basic params
    setBackground(BACKGROUND);
    
    // Setup scene viewer
    sceneViewer = new Window(this, "Scene Viewer");
    sceneViewer->setLayout(new GroupLayout(PADDING));
    
    // Setup the canvas in the scene viewer
    scene = new Scene(sceneViewer);
    scene->setBackgroundColor(BACKGROUND);
    scene->setSize(w - 2 * PADDING, h - HEADER_HEIGHT - 2 * PADDING);
    
    // Render the UI
    performLayout();
}

Viewer::~Viewer() {}

Scene & Viewer::getScene() {
    return *scene;
}

Camera & Viewer::getCamera() {
    return scene->getCamera();
}

bool Viewer::keyboardEvent(int key, int scancode, int action, int modifiers) {
    if (Screen::keyboardEvent(key, scancode, action, modifiers)) {
        return true;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        setVisible(false);
        return true;
    }
    return false;
}

void Viewer::draw(NVGcontext * ctx) {
    Screen::draw(ctx);
}

void Viewer::createViewer(int w, int h, std::string name, std::function<void(Viewer &)> init) {
    try {
        nanogui::init();
        
        // Initiate Viewer
        Viewer viewer = Viewer(w, h, name);
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
