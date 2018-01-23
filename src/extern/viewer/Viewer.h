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
        protected:
            
            int width;
            int height;
            bool cameraRotate;
            
            rotamina::Camera camera;
            std::vector<rotamina::Object *> objects;
            
            float prevTime = 0;
            
            Viewer(int width, int height, std::string name);
            ~Viewer();
            
            virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);
            virtual bool resizeEvent(const Eigen::Vector2i & size);
            
            virtual void draw(NVGcontext * ctx);
            virtual void drawContents();
            
        public:
            
            void setCameraRotate(bool flag);
            Camera & getCamera();
            void addObject(rotamina::Object & obj);
            
            static void createViewer(int width, int height, std::string name, std::function<void(Viewer &)> f);
    };
}

#endif
