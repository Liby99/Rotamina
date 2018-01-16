#ifndef VIEWER_H
#define VIEWER_H

#include <nanogui/opengl.h>
#include <nanogui/glutil.h>
#include <nanogui/screen.h>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "camera/Camera.h"
#include "object/Object.h"

namespace rotamina {
    
    class Viewer : public nanogui::Screen {
        private:
            
            static Viewer * app;
            
            Camera camera;
            std::vector<rotamina::Object *> objects;
            
            Viewer(int width, int height, std::string name);
            ~Viewer();
            
            void setup(std::function<void()> f);
            void initiateLayout();
            virtual void draw(NVGcontext * ctx);
            virtual void drawContents();
            
        public:
            
            static void initiate(int width, int height, std::string name, std::function<void(Viewer &)> f);
    };
}

#endif
