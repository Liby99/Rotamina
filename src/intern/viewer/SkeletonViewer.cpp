#include "viewer/SkeletonViewer.h"

using namespace rotamina;

SkeletonViewer::SkeletonViewer(int w, int h, std::string name, Skeleton & skel) : Viewer::Viewer(w, h, name) {
    
    using namespace nanogui;
    
    sceneViewer->setPosition({ JOINTS_VIEWER_WIDTH, 0 });
    scene->setWidth(w - JOINTS_VIEWER_WIDTH - JOINT_INFO_VIEWER_WIDTH - 2 * PADDING);
    
    jointsViewer = new Window(this, "Skeleton Structure");
    jointsViewer->setPosition({ 0, 0 });
    jointsViewer->setSize({ JOINTS_VIEWER_WIDTH, h });
    
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
