#ifndef VIEWER_H
#define VIEWER_H

#include <nanogui/opengl.h>
#include <nanogui/glutil.h>
#include <nanogui/screen.h>

#include <cmath>
#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "camera/Camera.h"
#include "object/Object.h"

namespace rotamina {
    
    class Viewer : public nanogui::Screen {
        private:
            
            rotamina::Camera camera;
            std::vector<rotamina::Object *> objects;
            
            float prevTime = 0.0f;
            Eigen::Vector2i mousePos;
            bool keyboard[128];
            
            Viewer(int width, int height, std::string name);
            
            virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);
            virtual bool resizeEvent(const Eigen::Vector2i & size);
            
            virtual void draw(NVGcontext * ctx);
            virtual void drawContents();
            
        public:
            
            Camera & getCamera();
            void addObject(rotamina::Object & obj);
            rotamina::Object & getObject(int index);
            
            static void createViewer(int width, int height, std::string name, std::function<void(Viewer &)> f);
    };
}

#endif
