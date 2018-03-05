#include <rotamina/rotamina.h>

using namespace rotamina;

class ClothViewer : public Viewer {
public:
    ClothViewer(int w, int h, std::string name) : Viewer::Viewer(w, h, name) {

    }
};

int main() {
    nanogui::init();

    // Initiate Viewer
    Viewer viewer = Viewer(1280, 720, "Cloth Particle Test");
    viewer.drawAll();
    viewer.setVisible(true);

    Cloth * c = new Cloth(2, 2, 10, 10);
    Gravity gravity;
    c->addForceField(gravity);

    viewer.getScene().addObject(*c);

    nanogui::mainloop();

    delete c;

    nanogui::shutdown();
}
