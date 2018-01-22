#include <iostream>

#include "viewer/SkeletonViewer.h"

using namespace rotamina;

bool bvar = true;
int ivar = 12345678;
double dvar = 3.1415926;
float fvar = (float)dvar;
std::string strval = "A string";
nanogui::Color colval(0.5f, 0.5f, 0.7f, 1.f);

SkeletonViewer::SkeletonViewer(int width, int height, std::string name, Skeleton & skel) : Viewer::Viewer(width, height, name) {
    
    this->skel = &skel;
    this->skel->shader = new Shader();
    
    using namespace nanogui;
    
    FormHelper *gui = new FormHelper(this);
    
    ref<Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar);
    gui->addVariable("string", strval);

    gui->addGroup("Validating fields");
    gui->addVariable("int", ivar)->setSpinnable(true);
    gui->addVariable("float", fvar);
    gui->addVariable("double", dvar)->setSpinnable(true);

    gui->addVariable("Color", colval)
       ->setFinalCallback([](const Color &c) {
             std::cout << "ColorPicker Final Callback: ["
                       << c.r() << ", "
                       << c.g() << ", "
                       << c.b() << ", "
                       << c.w() << "]" << std::endl;
         });

    gui->addGroup("Other widgets");
    gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; });
    
    performLayout();
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
