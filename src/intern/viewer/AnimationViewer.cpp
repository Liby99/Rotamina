#include "viewer/AnimationViewer.h"

using namespace rotamina;

const int AnimationViewer::ANIMATION_CONTROL_HEIGHT = 50;

AnimationViewer::AnimationViewer(int w, int h, std::string n, Animator & animator) : Viewer(w, h, n) {
    
    this->animator = &animator;
    scene->addObject(animator);
    scene->getShader().initTwoLights();
    
    using namespace nanogui;
    
    int sh = h - 2 * HEADER_HEIGHT - ANIMATION_CONTROL_HEIGHT;
    scene->setHeight(sh);
    
    animationControlWindow = new Window(this, "Animation Control");
    animationControlWindow->setPosition({ 0, sh + HEADER_HEIGHT });
    animationControlWindow->setFixedSize({ w, HEADER_HEIGHT + ANIMATION_CONTROL_HEIGHT });
    animationControlWindow->setLayout(new GridLayout(Orientation::Horizontal, 1, Alignment::Middle, 10, 5));
    
    Widget * left = new Widget(animationControlWindow);
    left->setLayout(new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 6));
    
    playPauseBtn = new Button(left, "Play");
    playPauseBtn->setCallback([this] () {
        togglePlay();
    });
    
    timeText = new Label(left, "s");
    timeText->setFontSize(20);
    timeText->setWidth(100);
    scene->setDisplayCallback([this] () {
        this->displayCallback();
    });
    
    stopBtn = new Button(left, "Stop");
    stopBtn->setCallback([this] () {
        stop();
    });
    
    performLayout();
    
    play();
}

void AnimationViewer::displayCallback() {
    this->timeText->setCaption(this->animator->getStopWatch().getDurationString());
    performLayout();
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
    performLayout();
}

void AnimationViewer::pause() {
    playPauseBtn->setCaption("Play");
    this->animator->pause();
    performLayout();
}

void AnimationViewer::stop() {
    pause();
    this->animator->stop();
}
