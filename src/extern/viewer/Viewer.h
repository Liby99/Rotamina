#ifndef VIEWER_H

#include <nanogui/opengl.h>
#include <nanogui/glutil.h>
#include <nanogui/screen.h>

#include <string>

#include "viewer/Scene.h"

class Viewer : public nanogui::Screen {
    private:
        
        nanogui::GLShader mShader; // Temp
        
        // Scene
        // Scene * scene;
        
        void initiateLayout();
        virtual void draw(NVGcontext * ctx);
        virtual void drawContents();
        
    public:
        
        Viewer();
        ~Viewer();
        
        // Setters
        // void setScene(Scene & scene);
};

#endif
