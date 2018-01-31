#include "viewer/TexturedSkinViewer.h"

using namespace rotamina;

TexturedSkinViewer::TexturedSkinViewer(int w, int h, std::string name, TexturedSkin & skin) : SkinViewer(w, h, name, skin) {
    
    // Setup skin
    this->texturedSkin = &skin;
    
    // Then setup shaders
    this->origShader = &scene->getShader();
    this->textureShader = new Shader();
    this->textureShader->initTwoLightsTexture();
    
    // Then show the skin
    showSkin();
    
    // Modify the skin control
    using namespace nanogui;
    
    ((GridLayout *) skinControlPanel->layout())->setResolution(3);
    
    ((Button *) skinControlPanel->childAt(0))->setCaption("Show Skin with Texture");
    
    skinControlPanel->removeChild(1);
    
    Button * showSkinWithoutTextureBtn = new Button(skinControlPanel, "Show Skin without Texture");
    showSkinWithoutTextureBtn->setFlags(Button::RadioButton);
    showSkinWithoutTextureBtn->setCallback([this] () { this->showSkinWithoutTexture(); });
    
    Button * showSkeletonBtn = new Button(skinControlPanel, "Show Skeleton");
    showSkeletonBtn->setFlags(Button::RadioButton);
    showSkeletonBtn->setCallback([this] () { this->showSkeleton(); });
    
    performLayout();
}

TexturedSkinViewer::~TexturedSkinViewer() {
    
    // Restore scene status for the scene to free up original shader
    showSkeleton();
    
    // Then reset texture shader
    textureShader->free();
    delete textureShader;
}

void TexturedSkinViewer::createViewer(int w, int h, std::string name, TexturedSkin & skin, std::function<void(TexturedSkinViewer &)> init) {
    try {
        nanogui::init();
        TexturedSkinViewer viewer = TexturedSkinViewer(w, h, name, skin);
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

void TexturedSkinViewer::showSkeleton() {
    scene->setShader(*origShader);
    SkinViewer::showSkeleton();
}

void TexturedSkinViewer::showSkin() {
    scene->setShader(*textureShader);
    SkinViewer::showSkin();
    texturedSkin->setRenderTexture(true);
}

void TexturedSkinViewer::showSkinWithoutTexture() {
    scene->setShader(*origShader);
    SkinViewer::showSkin();
    texturedSkin->setRenderTexture(false);
}
