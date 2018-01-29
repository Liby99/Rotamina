#include "viewer/Viewer.h"

using namespace std;

int main () {
    try {
        nanogui::init();
        
        nanogui::ref<rotamina::Viewer> app = new rotamina::Viewer(1440, 960, "CSE 169 Project 1");
        app->drawAll();
        app->setVisible(true);
        nanogui::mainloop();
        
        nanogui::shutdown();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << endl;
        return -1;
    }

    return 0;
}
