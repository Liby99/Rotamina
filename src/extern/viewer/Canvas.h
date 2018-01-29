#ifndef CANVAS_H
#define CANVAS_H

#include <nanogui/nanogui.h>

namespace rotamina {
    class Canvas : public nanogui::GLCanvas {
        public:
            Canvas(Widget *);
            ~Canvas();
            void setRotation(nanogui::Vector3f);
            virtual void drawGL() override;
        protected:
            nanogui::GLShader mShader;
            Eigen::Vector3f mRotation;
    };
}

#endif
