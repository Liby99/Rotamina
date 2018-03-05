#include "viewer/ClothViewer.h"

using namespace rotamina;

const int ClothViewer::CONTROL_PANEL_WIDTH = 300;

ClothViewer::ClothViewer(int w, int h, std::string name, Cloth & c) : Viewer(w, h, name) {
    
    // Initiate cloth
    cloth = &c;
    scene->addObject(c);

    // Initiate Shader
    scene->getShader().initTwoLights();

    // Initiate GUI
    using namespace nanogui;
    sceneViewer->setFixedWidth(w - CONTROL_PANEL_WIDTH);
    sceneViewer->setPosition({ CONTROL_PANEL_WIDTH, 0 });

    FormHelper * form = new FormHelper(this);
    controlPanel = form->addWindow({ CONTROL_PANEL_WIDTH, h }, "Cloth Control");
    controlPanel->setFixedSize({ CONTROL_PANEL_WIDTH, h });
    controlPanel->setPosition({ 0, 0 });

    form->addGroup("Cloth Parameters");
    addVar(form, "Cloth Width", this->cloth->width);
    addVar(form, "Cloth Height", this->cloth->height);
    addVar(form, "X Subdivision", this->cloth->subdivision[0]);
    addVar(form, "Y Subdivision", this->cloth->subdivision[1]);

    form->addGroup("Cloth Fixtures");


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
