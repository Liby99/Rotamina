#include "viewer/SkeletonViewer.h"

using namespace rotamina;

const int SkeletonViewer::JOINTS_VIEWER_WIDTH = 280;
const int SkeletonViewer::JOINT_INFO_VIEWER_WIDTH = 280;

SkeletonViewer::SkeletonViewer(int w, int h, std::string name, Skeleton & skel) : Viewer::Viewer(w, h, name) {
    
    skeleton = &skel;
    scene->addObject(skel);
    
    using namespace nanogui;
    
    sceneViewer->setPosition({ JOINTS_VIEWER_WIDTH, 0 });
    scene->setWidth(w - JOINTS_VIEWER_WIDTH - JOINT_INFO_VIEWER_WIDTH - 2 * PADDING);
    
    jointsViewer = new Window(this, "Skeleton Structure");
    jointsViewer->setPosition({ 0, 0 });
    jointsViewer->setFixedSize({ JOINTS_VIEWER_WIDTH, h });
    jointsViewer->setLayout(new GroupLayout(0));
    VScrollPanel * scrollPanel = new VScrollPanel(jointsViewer);
    scrollPanel->setFixedSize(nanogui::Vector2i(JOINTS_VIEWER_WIDTH, h - HEADER_HEIGHT));
    Widget * jointsHolder = new Widget(scrollPanel);
    jointsHolder->setLayout(new GroupLayout());
    addJointButton(skel.getRoot(), jointsHolder);
    
    jointInfoViewer = new Window(this, "Joint Info");
    jointInfoViewer->setPosition({ w - JOINT_INFO_VIEWER_WIDTH, 0 });
    jointInfoViewer->setFixedSize({ JOINT_INFO_VIEWER_WIDTH, h });
    jointInfoViewer->setLayout(new GroupLayout());
    showJointInfo(skel.getRoot());
    
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
        this->showJointInfo(joint);
    });
    btn->setFlags(Button::RadioButton);
    for (Joint * j : joint->getChildren()) {
        addJointButton(j, parent);
    }
}

void SkeletonViewer::clearJointInfo() {
    int count = jointInfoViewer->childCount();
    for (int i = 0; i < count; i++) {
        jointInfoViewer->removeChild(0);
    }
    performLayout();
}

void SkeletonViewer::showJointInfo(rotamina::Joint * joint) {
    
    clearJointInfo();
    
    using namespace nanogui;
    
    // Title and Joint Type
    Label * l = new Label(jointInfoViewer, joint->getName());
    l->setFontSize(24);
    l->setFont("sans-bold");
    l = new Label(jointInfoViewer, "Type: " + joint->getJointType());
    l->setFontSize(18);
    
    // DOFS
    auto dofs = joint->getDOFs();
    l = new Label(jointInfoViewer, "Degrees of Freedom (" + std::to_string(dofs.size()) + ")");
    l->setFontSize(18);
    if (dofs.size() > 0) {
        Widget * w = new Widget(jointInfoViewer);
        GridLayout * layout = new GridLayout(Orientation::Horizontal, 2, Alignment::Maximum, 0, 5);
        layout->setMargin(5);
        layout->setColAlignment({ Alignment::Maximum, Alignment::Fill });
        layout->setSpacing(0, 10);
        w->setLayout(layout);
        for (auto dp : dofs) {
            DOF * dof = dp.second;
            new Label(w, dp.first + " :", "sans-bold");
            FloatBox<float> * fb = new FloatBox<float>(w);
            fb->setValue(dof->getValue());
            fb->setUnits("rad");
            fb->setDefaultValue("0.0");
            fb->setFixedSize(Vector2i(200, 24));
            fb->setFontSize(16);
            fb->setSpinnable(true);
            fb->setCallback([fb, dof] (const float & value) {
                dof->setValue(value);
                fb->setValue(dof->getValue());
            });
        }
    }
    
    // Variables
    auto vars = joint->getVars();
    l = new Label(jointInfoViewer, "Variables (" + std::to_string(vars.size()) + ")");
    l->setFontSize(18);
    if (vars.size() > 0) {
        Widget * w = new Widget(jointInfoViewer);
        GridLayout * layout = new GridLayout(Orientation::Horizontal, 2, Alignment::Maximum, 0, 5);
        layout->setMargin(5);
        layout->setColAlignment({ Alignment::Maximum, Alignment::Fill });
        layout->setSpacing(0, 10);
        w->setLayout(layout);
        for (auto var : vars) {
            l = new Label(w, var.first + " :", "sans-bold");
            l = new Label(w, var.second);
            l->setFixedWidth(200);
        }
    }
    
    performLayout();
}
