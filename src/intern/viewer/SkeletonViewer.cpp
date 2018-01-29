#include "viewer/SkeletonViewer.h"

using namespace rotamina;

SkeletonViewer::SkeletonViewer(int w, int h, std::string name, Skeleton & skel) : Viewer::Viewer(w, h, name) {
    
    skeleton = &skel;
    scene->addObject(skel);
    
    using namespace nanogui;
    
    sceneViewer->setPosition({ JOINTS_VIEWER_WIDTH, 0 });
    scene->setWidth(w - JOINTS_VIEWER_WIDTH - JOINT_INFO_VIEWER_WIDTH - 2 * PADDING);
    
    jointsViewer = new Window(this, "Skeleton Structure");
    jointsViewer->setPosition({ 0, 0 });
    jointsViewer->setSize({ JOINTS_VIEWER_WIDTH, h });
    jointsViewer->setLayout(new GroupLayout(0));
    VScrollPanel * scrollPanel = new VScrollPanel(jointsViewer);
    scrollPanel->setFixedSize(nanogui::Vector2i(JOINTS_VIEWER_WIDTH, h - HEADER_HEIGHT));
    Widget * jointsHolder = new Widget(scrollPanel);
    jointsHolder->setLayout(new GroupLayout());
    addJointButton(skel.getRoot(), jointsHolder);
    
    jointInfoViewer = new Window(this, "Joint Info");
    jointInfoViewer->setPosition({ w - JOINT_INFO_VIEWER_WIDTH, 0 });
    jointInfoViewer->setSize({ JOINT_INFO_VIEWER_WIDTH, h });
    
    performLayout();
}

void SkeletonViewer::createViewer(int w, int h, std::string name, Skeleton & skel, std::function<void(SkeletonViewer &)> init) {
    try {
        nanogui::init();
        SkeletonViewer viewer = SkeletonViewer(w, h, name, skel);
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

void SkeletonViewer::addJointButton(rotamina::Joint * joint, nanogui::Widget * parent) {
    using namespace nanogui;
    Button * btn = new Button(parent, joint->getName());
    btn->setFontSize(16);
    btn->setCallback([this, joint]() {
        // this->showJoint(joint);
    });
    btn->setFlags(Button::RadioButton);
    for (Joint * j : joint->getChildren()) {
        addJointButton(j, parent);
    }
}
