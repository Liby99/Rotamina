#include <iostream>

#include "viewer/SkeletonViewer.h"

using namespace rotamina;

SkeletonViewer::SkeletonViewer(int width, int height, std::string name, Skeleton & skel)
    : Viewer::Viewer(width, height, name) {
    
    this->skel = &skel;
    this->skel->shader = new Shader();
}

void SkeletonViewer::draw(NVGcontext * ctx) {
    Screen::draw(ctx);
}

void SkeletonViewer::drawContents() {
    
    Viewer::drawContents();
    
    skel->shader->bind();
    Eigen::Matrix4f vp = camera.getViewPerspective();
    Eigen::Matrix4f model = skel->transform.getTransform();
    Eigen::Matrix4f mvp = model * vp;
    skel->shader->setUniform("ModelMtx", model);
    skel->shader->setUniform("ModelViewProjMtx", mvp);
    skel->update();
    skel->draw();
}

void SkeletonViewer::createViewer(int width, int height, std::string name, Skeleton & skel, std::function<void(Viewer &)> init) {
    try {
        nanogui::init();
        
        // Initiate the viewer
        SkeletonViewer viewer(width, height, name, skel);
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
