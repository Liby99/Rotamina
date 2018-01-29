#ifndef CANVAS_H
#define CANVAS_H

#include <nanogui/nanogui.h>

#include <object/Object.h>

namespace rotamina {
    class Canvas : public nanogui::GLCanvas {
        protected:
            rotamina::Shader shader;
            rotamina::Camera camera;
            std::vector<rotamina::Object *> objects;
        public:
            Canvas(Widget *);
            ~Canvas();
            virtual void drawGL() override;
    };
}

#endif
