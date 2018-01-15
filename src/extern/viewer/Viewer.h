#ifndef VIEWER_H

#include <nanogui/opengl.h>
#include <nanogui/glutil.h>
#include <nanogui/screen.h>

#include <iostream>
#include <string>
#include <functional>

#include "viewer/Scene.h"

class Viewer : public nanogui::Screen {
    private:
        
        nanogui::GLShader mShader; // Temp
        static Viewer * app;
        
        // Scene
        // Scene * scene;
        
        Viewer(int width, int height, std::string);
        ~Viewer();
        
        void setup(std::function<void()> f);
        void initiateLayout();
        virtual void draw(NVGcontext * ctx);
        virtual void drawContents();
        
    public:
        
        static void initiate(int width, int height, std::string name, std::function<void(Viewer &)> f);
        
        // Setters
        // void setScene(Scene & scene);
};

#endif
