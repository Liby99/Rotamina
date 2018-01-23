#include <iostream>

#include "viewer/SkeletonViewer.h"

using namespace rotamina;

float a = 3;

SkeletonViewer::SkeletonViewer(int width, int height, std::string name, Skeleton & skel) : Viewer::Viewer(width, height, name) {
    
    joints = nullptr;
    jointData = nullptr;
    form = nullptr;
    
    this->skel = &skel;
    this->skel->shader = new Shader();
    
    using namespace nanogui;
    
    // Joint List Window
    joints = new Window(this, "Skeleton Joint List");
    joints->setPosition(Vector2i(15, 15));
    joints->setFixedSize(nanogui::Vector2i(250, height - 30));
    joints->setLayout(new GroupLayout(0));
    
    VScrollPanel * scrollPanel = new VScrollPanel(joints);
    scrollPanel->setFixedSize(nanogui::Vector2i(250, height - 50));
    
    Widget * jointButtons = new Widget(scrollPanel);
    jointButtons->setLayout(new GroupLayout());
    
    Joint * root = this->skel->getRoot();
    addButton(root, jointButtons, 0);
    
    // Joint Data Window
    form = new FormHelper(this);
    jointData = form->addWindow(Eigen::Vector2i(width - 215, 15), "Joint Data");
    jointData->setFixedWidth(200);
    
    performLayout();
}

void SkeletonViewer::draw(NVGcontext * ctx) {
    form->refresh();
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

void SkeletonViewer::clearJointData() {
    
    jointData->setVisible(false);
    
    jointData = form->addWindow(Eigen::Vector2i(width - 215, 15), "Joint Data");
    jointData->setFixedWidth(200);
    
    performLayout();
}

void SkeletonViewer::showJoint(Joint * joint) {
    
    clearJointData();
    
    form->addGroup(joint->getName());
    auto dofs = joint->getDOFs();
    for (auto dp : dofs) {
        DOF * dof = dp.second;
        form->addVariable<float>(dp.first, [dof] (const float & value) {
            dof->setValue(value);
        }, [dof] () {
            return dof->getValue();
        })->setSpinnable(true);
    }
    
    performLayout();
}

void SkeletonViewer::addButton(Joint * joint, nanogui::Widget * parent, int margin) {
    
    using namespace nanogui;
    
    Button * btn = new Button(parent, joint->getName());
    btn->setFontSize(14);
    btn->setCallback([this, joint]() {
        this->showJoint(joint);
    });
    for (Joint * j : joint->getChildren()) {
        addButton(j, parent, margin + 3);
    }
}
