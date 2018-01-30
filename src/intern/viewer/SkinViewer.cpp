#include "viewer/SkinViewer.h"

using namespace rotamina;

SkinViewer::SkinViewer(int w, int h, std::string name, Skin & skin) : SkeletonViewer(w, h, name, skin.getSkeleton()) {
    this->skin = &skin;
    scene->removeObject(0);
    scene->addObject(skin);
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
