#include "viewer/Viewer.h"

using namespace rotamina;

Viewer::Viewer(int w, int h, std::string name) : nanogui::Screen(Eigen::Vector2i(w, h), name, false) {
    
    using namespace nanogui;
    
    // Set basic params
    setBackground(BACKGROUND);
    
    // Setup scene viewer
    sceneViewer = new Window(this, "Scene Viewer");
    sceneViewer->setLayout(new GroupLayout(PADDING));
    
    // Setup the canvas in the scene viewer
    scene = new Canvas(sceneViewer);
    scene->setBackgroundColor(BACKGROUND);
    scene->setSize({ w - 2 * PADDING, h - HEADER_HEIGHT - 2 * PADDING });
    
    // Render the UI
    performLayout();
}

Viewer::~Viewer() {}

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
