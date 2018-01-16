#ifndef VIEWER_H
#define VIEWER_H

#include <nanogui/opengl.h>
#include <nanogui/glutil.h>
#include <nanogui/screen.h>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

class Viewer : public nanogui::Screen {
    private:
        
        static Viewer * app;
        
        nanogui::GLShader shader; // Temp
        
        // Scene
        // Camera * camera;
        // std::vector<Object *> objects;
        
        Viewer(int width, int height, std::string name);
        ~Viewer();
        
        void setup(std::function<void()> f);
        void initiateLayout();
        virtual void draw(NVGcontext * ctx);
        virtual void drawContents();
        
    public:
        
        static void initiate(int width, int height, std::string name, std::function<void(Viewer &)> f);
};

#endif
