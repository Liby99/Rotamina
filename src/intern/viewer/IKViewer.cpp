#include "viewer/IKViewer.h"

using namespace rotamina;

const int IKViewer::TARGET_CONTROL_HEIGHT = 300;

IKViewer::IKViewer(int w, int h, std::string n, IKSkeleton & skel) : SkeletonViewer(w, h, n, skel) {

    using namespace nanogui;

    jointInfoViewer->setFixedHeight(h - TARGET_CONTROL_HEIGHT);

    targetControlWindow = new Window(this, "Targets");
    targetControlWindow->setFixedSize({ JOINT_INFO_VIEWER_WIDTH, TARGET_CONTROL_HEIGHT });
    targetControlWindow->setPosition({ w - JOINT_INFO_VIEWER_WIDTH, h - TARGET_CONTROL_HEIGHT });
    targetControlWindow->setLayout(new GroupLayout(0));
    VScrollPanel * scrollPanel = new VScrollPanel(targetControlWindow);
    scrollPanel->setFixedSize({ TARGET_CONTROL_HEIGHT, JOINT_INFO_VIEWER_WIDTH });
    Widget * targetsHolder = new Widget(scrollPanel);
    targetsHolder->setLayout(new GroupLayout());

    for (auto it = skel.targets.begin(); it != skel.targets.end(); it++) {
        new Label(targetsHolder, it->first->getName());
        Widget * w = new Widget(targetsHolder);
        GridLayout * layout = new GridLayout(Orientation::Horizontal, 2, Alignment::Fill, 0, 5);
        layout->setMargin(5);
        layout->setColAlignment({ Alignment::Middle, Alignment::Middle });
        layout->setSpacing(0, 10);
        Cube * c = new Cube(0.1, 0.1, 0.1);
        c->transform.position = it->second;
        scene->addObject(*c);
        targetIndicators.push_back(c);
        w->setLayout(layout);
        for (int i = 0; i < 3; i++) {
            std::string l(1, char('x' + i));
            new Label(w, l + " :", "sans-bold");
            FloatBox<float> * fb = new FloatBox<float>(w);
            Vector3f & v = it->second;
            fb->setValue(it->second[i]);
            fb->setUnits("rad");
            fb->setDefaultValue("0.0");
            fb->setFixedSize(Vector2i(120, 24));
            fb->setFontSize(16);
            fb->setSpinnable(true);
            fb->setCallback([&v, i, c] (const float & value) {
                v(i) = value;
                c->transform.position = v;
            });
        }
    }

    scene->setDisplayCallback([this] () {
        this->showJointInfo(this->currJoint);
    });

    performLayout();
}

IKViewer::~IKViewer() {
    for (int i = 0; i < targetIndicators.size(); i++) {
        delete targetIndicators[i];
    }
}

void IKViewer::createViewer(int w, int h, std::string name, IKSkeleton & skel) {
    try {
        nanogui::init();
        IKViewer viewer = IKViewer(w, h, name, skel);
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
