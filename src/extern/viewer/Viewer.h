#ifndef VIEWER_H
#define VIEWER_H

#include <string>
#include <nanogui/nanogui.h>

#include "Canvas.h"

namespace rotamina {
    class Viewer : public nanogui::Screen {
        private:
            nanogui::Color BACKGROUND = { 30, 30, 30, 255 };
            int HEADER_HEIGHT = 28;
            int PADDING = 5;
        protected:
            nanogui::Window * sceneViewer;
            rotamina::Canvas * scene;
        public:
            Viewer(int, int, std::string);
            ~Viewer();
            virtual bool keyboardEvent(int, int, int, int);
            virtual void draw(NVGcontext *);
            static void createViewer();
    };
}

#endif
