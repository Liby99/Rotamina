#include "viewer/SkinViewer.h"

using namespace rotamina;

SkinViewer::SkinViewer(int w, int h, std::string name, Skin & skin) : SkeletonViewer(w, h, name, skin.getSkeleton()) {
    
    // Initiate basic variables
    this->skin = &skin;
    
    // Load scene
    scene->addObject(skin);
    scene->getShader().initTwoLights();
    
    // Initiate visibility. Show the skin and hide the skeleton
    showSkin();
    
    // Initiate
    using namespace nanogui;
    
    scene->setHeight(h - CONTROL_PANEL_HEIGHT - 2 * HEADER_HEIGHT - 2 * PADDING);
    sceneViewer->setHeight(h - CONTROL_PANEL_HEIGHT - HEADER_HEIGHT);
    
    skinControlPanel = new Window(this, "Skin Control");
    skinControlPanel->setPosition({ JOINTS_VIEWER_WIDTH, h - CONTROL_PANEL_HEIGHT - HEADER_HEIGHT });
    skinControlPanel->setFixedSize({ w - JOINTS_VIEWER_WIDTH - JOINT_INFO_VIEWER_WIDTH, CONTROL_PANEL_HEIGHT + HEADER_HEIGHT });
    GridLayout * layout = new GridLayout(Orientation::Horizontal, 2, Alignment::Middle, 10, 5);
    skinControlPanel->setLayout(layout);
    
    Button * showSkinBtn = new Button(skinControlPanel, "Show Skin");
    showSkinBtn->setFlags(Button::RadioButton);
    showSkinBtn->setPushed(true);
    showSkinBtn->setCallback([this] () { this->showSkin(); });
    Button * showSkelBtn = new Button(skinControlPanel, "Show Skeleton");
    showSkelBtn->setFlags(Button::RadioButton);
    showSkelBtn->setCallback([this] () { this->showSkeleton(); });
    
    // Reset focus
    sceneViewer->requestFocus();
    
    // performLayout
    performLayout();
}

void SkinViewer::createViewer(int w, int h, std::string name, Skin & skin, std::function<void(SkinViewer &)> init) {
    try {
        nanogui::init();
        SkinViewer viewer = SkinViewer(w, h, name, skin);
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

void SkinViewer::showSkeleton() {
    this->skin->setHidden(true);
    this->skeleton->setHidden(false);
}

void SkinViewer::showSkin() {
    this->skin->setHidden(false);
    this->skeleton->setHidden(true);
}
