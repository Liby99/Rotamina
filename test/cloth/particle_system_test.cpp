#include <iostream>
#include <rotamina/rotamina.h>

using namespace rotamina;

int main() {
    nanogui::init();

    Cloth c(5, 5, 15, 15);
    Gravity gravity;
    c.addForceField(gravity);
    c.transform.position = Eigen::Vector3f(0, 1, 0);

    // Initiate Viewer
    ClothViewer viewer = ClothViewer(1280, 720, "Cloth Particle Test", c);
    viewer.drawAll();
    viewer.setVisible(true);

    nanogui::mainloop();
    nanogui::shutdown();
}
