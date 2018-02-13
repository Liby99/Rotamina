#include "viewer/AnimationViewer.h"

using namespace rotamina;

AnimationViewer::AnimationViewer(int w, int h, std::string n, Animator & animator) : Viewer(w, h, n) {
    this->animator = &animator;
    scene->addObject(animator);
    scene->getShader().initTwoLights();
    animator.start();
}

void AnimationViewer::create(int w, int h, std::string name, Animator & a, std::function<void(AnimationViewer &)> init) {
    try {
        nanogui::init();
        AnimationViewer viewer = AnimationViewer(w, h, name, a);
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
