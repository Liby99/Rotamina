#ifndef SKIN_VIEWER_H
#define SKIN_VIEWER_H

#include <nanogui/nanogui.h>

namespace rotamina {
    
    class Canvas : public nanogui::GLCanvas {
        public:
            SkinCanvas(Widget *);
            ~SkinCanvas();
            void setRotation(nanogui::Vector3f);
            virtual void drawGL() override;
        private:
            nanogui::GLShader mShader;
            Eigen::Vector3f mRotation;
    };
    
    class Viewer : public nanogui::Screen {
        private:
            SkinCanvas * canvas;
        public:
            SkinViewer();
            virtual bool keyboardEvent(int, int, int, int);
            virtual void draw(NVGcontext *);
    };
}

#endif
