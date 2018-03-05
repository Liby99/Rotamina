#include "viewer/ClothViewer.h"

using namespace rotamina;

const int ClothViewer::CONTROL_PANEL_WIDTH = 300;
const int ClothViewer::PLAYBACK_PANEL_HEIGHT = 80;

ClothViewer::ClothViewer(int w, int h, std::string name, Cloth & c) : Viewer(w, h, name) {
    
    // Initiate cloth
    cloth = &c;
    scene->addObject(c);

    // Initiate Shader
    scene->getShader().initTwoLights();

    // Initiate GUI
    using namespace nanogui;
    sceneViewer->setFixedSize({ w - CONTROL_PANEL_WIDTH, h - PLAYBACK_PANEL_HEIGHT });
    sceneViewer->setPosition({ CONTROL_PANEL_WIDTH, 0 });
    sceneViewer->childAt(0)->setFixedHeight(h - PLAYBACK_PANEL_HEIGHT - HEADER_HEIGHT - 2 * PADDING);

    FormHelper * form = new FormHelper(this);
    controlPanel = form->addWindow({ CONTROL_PANEL_WIDTH, h }, "Cloth Control");
    controlPanel->setFixedSize({ CONTROL_PANEL_WIDTH, h });
    controlPanel->setPosition({ 0, 0 });

    form->addGroup("Cloth Fixtures");
    Button * lb = form->addButton("Fix Left Side", [this] () {
        this->cloth->resetFixture();
        float hw = this->cloth->width / 2, hh = this->cloth->height / 2,
                sy = this->cloth->height / this->cloth->subdivision[1];
        for (int j = 0; j <= this->cloth->subdivision[1]; j++) {
            ClothParticle & cp = this->cloth->getParticle(0, j);
            cp.fixed = true;
            cp.position[0] = -hw;
            cp.position[1] = hh - j * sy;
            cp.position[2] = 0;
        }
    });
    lb->setFlags(Button::RadioButton);
    Button * tb = form->addButton("Fix Top", [this] () {
        this->cloth->resetFixture();
        float hw = this->cloth->width / 2, hh = this->cloth->height / 2,
                sx = this->cloth->width / this->cloth->subdivision[0];
        for (int i = 0; i <= this->cloth->subdivision[1]; i++) {
            ClothParticle & cp = this->cloth->getParticle(i, 0);
            cp.fixed = true;
            cp.position[0] = -hw + i * sx;
            cp.position[1] = hh;
            cp.position[2] = 0;
        }
    });
    tb->setFlags(Button::RadioButton);
    Button * ttcb = form->addButton("Two Top Corners", [this] () {
        this->cloth->resetFixture();
        float hw = this->cloth->width / 2, hh = this->cloth->height / 2;
        ClothParticle & ul = this->cloth->getParticle(0, 0);
        ul.fixed = true;
        ul.position[0] = -hw;
        ul.position[1] = hh;
        ul.position[2] = 0;
        ClothParticle & ur = this->cloth->getParticle(this->cloth->subdivision[0], 0);
        ur.fixed = true;
        ur.position[0] = hw;
        ur.position[1] = hh;
        ur.position[2] = 0;
    });
    ttcb->setFlags(Button::RadioButton);

    form->addGroup("Physics System");
    addVar(form, "Iteration Count", this->cloth->iterationCount);

    form->addGroup("Gravity");
    addVar(form, "Gravity", ((Gravity *) (this->cloth->fields[0]))->g);

    form->addGroup("Material Properties");
    addVar(form, "Spring Constant", this->cloth->springConstant);
    addVar(form, "Damping Factor", this->cloth->dampingFacter);

    form->addGroup("Wind Properties");
    addVar(form, "Wind Speed X", this->cloth->windSpeed[0]);
    addVar(form, "Wind Speed Y", this->cloth->windSpeed[1]);
    addVar(form, "Wind Speed Z", this->cloth->windSpeed[2]);
    addVar(form, "Air Density", this->cloth->airDensity);
    addVar(form, "Drag Coefficient", this->cloth->dragCoefficient);

    form->addGroup("Ground Properties");
    addVar(form, "Ground Altitude", this->cloth->groundHeight);
    addVar(form, "Elasticity", this->cloth->elasticity);
    addVar(form, "Friction", this->cloth->friction);

    form->addGroup("Reset");
    Button * reset = form->addButton("Reset", [this] () {
        this->cloth->reset();
    });
    reset->setBackgroundColor(Color(125, 0, 0, 125));

    Window * playWindow = new Window(this, "Playback");
    playWindow->setPosition({ CONTROL_PANEL_WIDTH, h - PLAYBACK_PANEL_HEIGHT });
    playWindow->setFixedSize({ w - CONTROL_PANEL_WIDTH, PLAYBACK_PANEL_HEIGHT });
    playWindow->setLayout(new GridLayout());
    Button * play = new Button(playWindow, "Play");
    play->setCallback([this] () {
        this->cloth->stopWatch.start();
    });
    Button * pause = new Button(playWindow, "Pause");
    pause->setCallback([this] () {
        this->cloth->stopWatch.pause();
    });

    // Perform Layout in the end
    performLayout();
}

void ClothViewer::addVar(nanogui::FormHelper * form, std::string name, float & f) {
    auto v = form->addVariable(name, f);
    v->setSpinnable(true);
    v->setCallback([&f] (float value) {
        f = value;
    });
}

void ClothViewer::addVar(nanogui::FormHelper * form, std::string name, int & i) {
    auto v = form->addVariable(name, i);
    v->setSpinnable(true);
    v->setCallback([&i] (int value) {
        i = value;
    });
}
