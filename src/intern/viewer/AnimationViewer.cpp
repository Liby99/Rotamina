#include "viewer/AnimationViewer.h"

using namespace rotamina;

const int AnimationViewer::ANIMATION_CONTROL_HEIGHT = 50;

AnimationViewer::AnimationViewer(int w, int h, std::string n, Animator & animator) : Viewer(w, h, n) {
    this->animator = &animator;
    scene->addObject(animator);
    scene->getShader().initTwoLights();

    using namespace nanogui;

    int sh = h - 2 * HEADER_HEIGHT - 2 * PADDING - ANIMATION_CONTROL_HEIGHT;
    scene->setHeight(sh);

    animationControlWindow = new Window(this, "Animation Control");
    animationControlWindow->setPosition({ 0, sh });
    animationControlWindow->setFixedSize({ w - PADDING, HEADER_HEIGHT + ANIMATION_CONTROL_HEIGHT });
    animationControlWindow->setLayout(new GridLayout(Orientation::Horizontal, 2, Alignment::Middle, 10, 5));

    playPauseBtn = new Button(animationControlWindow, "Play");
    playPauseBtn->setCallback([this] () {
        togglePlay();
    });
    stopBtn = new Button(animationControlWindow, "Stop");
    stopBtn->setCallback([this] () {
        stop();
    });

    performLayout();

    play();
}

void AnimationViewer::create(int w, int h, std::string name, Animator & a, std::function<void(AnimationViewer &)> init) {
    try {
        nanogui::init();
        AnimationViewer viewer = AnimationViewer(w, h, name, a);
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

void AnimationViewer::togglePlay() {
    if (isPlaying()) pause();
    else play();
}

bool AnimationViewer::isPlaying() {
    return this->animator->isPlaying();
}

void AnimationViewer::play() {
    playPauseBtn->setCaption("Pause");
    this->animator->start();
}

void AnimationViewer::pause() {
    playPauseBtn->setCaption("Play");
    this->animator->pause();
}

void AnimationViewer::stop() {
    pause();
    this->animator->stop();
}
