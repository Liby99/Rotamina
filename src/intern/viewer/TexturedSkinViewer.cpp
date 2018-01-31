#include "viewer/TexturedSkinViewer.h"

using namespace rotamina;

TexturedSkinViewer::TexturedSkinViewer(int w, int h, std::string name, TexturedSkin & skin) : SkinViewer(w, h, name, skin) {
    showSkin();
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
    scene->getShader().initTwoLights();
    SkinViewer::showSkeleton();
}

void TexturedSkinViewer::showSkin() {
    scene->getShader().initTwoLightsTexture();
    SkinViewer::showSkin();
}
