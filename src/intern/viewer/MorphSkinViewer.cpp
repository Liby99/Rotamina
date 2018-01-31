#include "viewer/MorphSkinViewer.h"

using namespace rotamina;

const int MorphSkinViewer::MORPH_CONTROL_HEIGHT = 400;

MorphSkinViewer::MorphSkinViewer(int w, int h, std::string name, MorphSkin & skin) : TexturedSkinViewer(w, h, name, skin) {
    
    // Setup instance variable
    this->morphSkin = &skin;
    
    // Initiate UI Elements
    using namespace nanogui;
    
    // Reset the size of original windows
    jointsViewer->setFixedHeight(h - MORPH_CONTROL_HEIGHT);
    jointsViewer->children()[0]->setFixedHeight(h - HEADER_HEIGHT - MORPH_CONTROL_HEIGHT);
    
    // Add new morph control panel
    morphControlWindow = new Window(this, "Morph Control");
    morphControlWindow->setPosition({ 0, h - MORPH_CONTROL_HEIGHT });
    morphControlWindow->setFixedSize({ JOINTS_VIEWER_WIDTH, MORPH_CONTROL_HEIGHT });
    morphControlWindow->setLayout(new GroupLayout(0));
    VScrollPanel * scrollPanel = new VScrollPanel(morphControlWindow);
    scrollPanel->setFixedSize({ JOINTS_VIEWER_WIDTH, MORPH_CONTROL_HEIGHT - HEADER_HEIGHT });
    Widget * weightsHolder = new Widget(scrollPanel);
    weightsHolder->setLayout(new GroupLayout());
    
    // For each weight add slider to it
    std::vector<float> & weights = this->morphSkin->getWeights();
    for (int i = 0; i < weights.size(); i++) {
        
        // Add label and slider
        new Label(weightsHolder, "Morph " + std::to_string(i + 1) + ": ");
        Slider * slider = new Slider(weightsHolder);
        slider->setCallback([this, i] (float p) {
            this->morphSkin->setWeight(i, p);
        });
    }
    
    performLayout();
}

void MorphSkinViewer::createViewer(int w, int h, std::string name, MorphSkin & skin, std::function<void(MorphSkinViewer &)> init) {
    try {
        nanogui::init();
        MorphSkinViewer viewer = MorphSkinViewer(w, h, name, skin);
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
