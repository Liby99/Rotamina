#include <iostream>
#include <rotamina/rotamina.h>

using namespace rotamina;

class ClothViewer : public Viewer {
public:
    ClothViewer(int w, int h, std::string name) : Viewer::Viewer(w, h, name) {
        scene->getShader().initTwoLights();
    }
};

int main() {
    nanogui::init();

    // Initiate Viewer
    ClothViewer viewer = ClothViewer(1280, 720, "Cloth Particle Test");
    viewer.drawAll();
    viewer.setVisible(true);

    Cloth * c = new Cloth(2, 1, 100, 50);
    Gravity gravity;
    c->addForceField(gravity);

    c->transform.position = Eigen::Vector3f(0, 1, 0);

    viewer.getScene().addObject(*c);

    nanogui::mainloop();

    delete c;

    nanogui::shutdown();
}
