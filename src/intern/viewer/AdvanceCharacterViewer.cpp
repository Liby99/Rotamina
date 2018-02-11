#include "viewer/AdvanceCharacterViewer.h"

using namespace rotamina;

const int AdvanceCharacterViewer::MORPH_CONTROL_HEIGHT = 400;

AdvanceCharacterViewer::AdvanceCharacterViewer(int w, int h, std::string name, AdvanceCharacter & c) : CharacterViewer(w, h, name, c) {
    
    // Setup character
    this->advanceCharacter = &c;
    
    // Setup shaders
    this->origShader = &scene->getShader();
    this->textureShader = new Shader();
    this->textureShader->initTwoLightsTexture();
    
    using namespace nanogui;
    
    // Initiate Texture GUI
    {
        
        ((GridLayout *) skinControlPanel->layout())->setResolution(3);
        
        ((Button *) skinControlPanel->childAt(0))->setCaption("Show Skin with Texture");
        
        skinControlPanel->removeChild(1);
        
        Button * showSkinWithoutTextureBtn = new Button(skinControlPanel, "Show Skin without Texture");
        showSkinWithoutTextureBtn->setFlags(Button::RadioButton);
        showSkinWithoutTextureBtn->setCallback([this] () { this->showSkinWithoutTexture(); });
        
        Button * showSkeletonBtn = new Button(skinControlPanel, "Show Skeleton");
        showSkeletonBtn->setFlags(Button::RadioButton);
        showSkeletonBtn->setCallback([this] () { this->showSkeleton(); });
    }
    
    // Initiate Morph GUI
    {
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
        std::vector<float> & weights = this->advanceCharacter->getSkin().getWeights();
        for (int i = 0; i < weights.size(); i++) {
            
            // Add label and slider
            new Label(weightsHolder, "Morph " + std::to_string(i + 1) + ": ");
            Slider * slider = new Slider(weightsHolder);
            slider->setCallback([this, i] (float p) {
                this->advanceCharacter->getSkin().setWeight(i, p);
            });
        }
    }
    
    performLayout();
}

AdvanceCharacterViewer::~AdvanceCharacterViewer() {
    showSkeleton();
    textureShader->free();
    delete textureShader;
}

void AdvanceCharacterViewer::showSkeleton() {
    scene->setShader(*origShader);
    CharacterViewer::showSkeleton();
}

void AdvanceCharacterViewer::showSkin() {
    scene->setShader(*textureShader);
    CharacterViewer::showSkin();
    advanceCharacter->getSkin().setRenderTexture(true);
}

void AdvanceCharacterViewer::showSkinWithoutTexture() {
    scene->setShader(*origShader);
    CharacterViewer::showSkin();
    advanceCharacter->getSkin().setRenderTexture(false);
}
