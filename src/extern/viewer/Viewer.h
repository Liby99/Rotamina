#ifndef VIEWER_H
#define VIEWER_H

#include <string>
#include <functional>
#include <nanogui/nanogui.h>

#include "viewer/component/Scene.h"

namespace rotamina {
    class Viewer : public nanogui::Screen {
        protected:
            
            // Basic constants
            static const nanogui::Color BACKGROUND;
            static const int HEADER_HEIGHT;
            static const int PADDING;
            
            // Variables
            nanogui::Window * sceneViewer;
            rotamina::Scene * scene;
            
        public:
            
            // Constructor
            Viewer(int, int, std::string);
            ~Viewer();
            
            // Basic getter setters
            bool isSceneFocusing();
            rotamina::Scene & getScene();
            rotamina::Camera & getCamera();
            
            // Event Handling
            virtual bool keyboardEvent(int, int, int, int);
            virtual void draw(NVGcontext *);
            
            // Static Singleton Methods
            static void createViewer(int, int, std::string, std::function<void(Viewer &)>);
    };
}

#endif
