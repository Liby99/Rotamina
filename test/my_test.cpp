#include <iostream>
#include <string>

#include "viewer/Viewer.h"

int main() {
    try {
        nanogui::init();

        {
            nanogui::ref<Viewer> app = new Viewer();
            app->drawAll();
            app->setVisible(true);
            nanogui::mainloop();
        }

        nanogui::shutdown();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
        return -1;
    }

    return 0;
}
