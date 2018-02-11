#include "viewer/CharacterViewer.h"

using namespace rotamina;

CharacterViewer::CharacterViewer(int w, int h, std::string name, Character & character)
    : SkeletonViewer(w, h, name, character.getSkeleton()) {

    // Initiate basic variables
    this->character = &character;

    // Load scene
    scene->removeObject(0);
    scene->addObject(character);
    scene->getShader().initTwoLights();

    // Initiate GUI
    using namespace nanogui;

    scene->setHeight(h - CONTROL_PANEL_HEIGHT - 2 * HEADER_HEIGHT - 2 * PADDING);
    sceneViewer->setHeight(h - CONTROL_PANEL_HEIGHT - HEADER_HEIGHT);

    skinControlPanel = new Window(this, "Character Render");
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

void CharacterViewer::create(int w, int h, std::string name, Character & character, std::function<void(CharacterViewer &)> init) {
    try {
        nanogui::init();
        CharacterViewer viewer = CharacterViewer(w, h, name, character);
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

void CharacterViewer::showSkeleton() {
    character->setShowSkeleton();
}

void CharacterViewer::showSkin() {
    character->setShowSkin();
}
